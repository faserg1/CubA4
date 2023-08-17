#include <audio/AudioImporter.hpp>
#include <audio/IAudioBufferPool.hpp>
#include <audio/IAudioBuffer.hpp>
#include <vorbis/codec.h>
#include <ogg/ogg.h>
#include <stdexcept>
#include <vector>
#include <array>
#include <span>
using namespace CubA4::audio;
using namespace CubA4::resources;

AudioImporter::AudioImporter(IAudioBufferPool &bufferPool) :
	bufferPool_(bufferPool)
{

}


// TODO: thing about RAII

struct OggInfo
{
	ogg_sync_state syncState;
	ogg_page page;
	ogg_stream_state streamState;
	ogg_packet packet;
};

const uint32_t oggReadSize = 4096;
const uint32_t initialConvSize = 4096;
size_t readOggPageBuffer(std::shared_ptr<const IResource> resource, size_t &resourceOffset, OggInfo &info, bool pageIn = true);
bool readOggPacket(OggInfo &info);

std::shared_ptr<IAudioBuffer> AudioImporter::importTrack(std::shared_ptr<const IResource> resource)
{
	return createFromOgg(resource);
}

std::shared_ptr<IAudioBuffer> AudioImporter::createFromOgg(std::shared_ptr<const IResource> resource)
{
	auto buffer = bufferPool_.getBuffer();

	OggInfo ogg;

	ogg_sync_init(&ogg.syncState);

	vorbis_info vorbisInfo;
	vorbis_comment vorbisComment;
	vorbis_dsp_state vorbisState;
	vorbis_block vorbisBlock;

	std::vector<ogg_int16_t> samplesBuffer;
	size_t samplesOffset = 0;
	uint32_t convSize = initialConvSize;

	size_t resourcedReaded = 0;

	readOggPageBuffer(resource, resourcedReaded, ogg, false);

	ogg_stream_init(&ogg.streamState, ogg_page_serialno(&ogg.page));

	vorbis_info_init(&vorbisInfo);
	vorbis_comment_init(&vorbisComment);

	uint8_t vorbisHeadersCount = 0;

	if(ogg_stream_pagein(&ogg.streamState, &ogg.page)<0)
	{
		/* error; stream version mismatch perhaps */
		//fprintf(stderr,"Error reading first page of Ogg bitstream data.\n");
		//exit(1);
		return {};
	}
	
	if (ogg_stream_packetout(&ogg.streamState, &ogg.packet)!=1)
	{ 
		/* no page? must not be vorbis */
		//fprintf(stderr,"Error reading initial header packet.\n");
		//exit(1);
		return {};
	}
	
	if (vorbis_synthesis_headerin(&vorbisInfo, &vorbisComment, &ogg.packet) < 0)
	{ 
		/* error case; not a vorbis header */
		//fprintf(stderr,"This Ogg bitstream does not contain Vorbis audio data.\n");
		//exit(1);
		return {};
	}

	vorbisHeadersCount++;

	// reading pages for headers
	while (true)
	{
		readOggPageBuffer(resource, resourcedReaded, ogg);

		do {
			if (!readOggPacket(ogg))
				break;
			if (!vorbis_synthesis_headerin(&vorbisInfo, &vorbisComment, &ogg.packet)) {
				vorbisHeadersCount++;
			}
		} while (vorbisHeadersCount < 3);

		if (vorbisHeadersCount == 3)
			break;
	}

	convSize = initialConvSize / vorbisInfo.channels;
	const auto channelsCount = vorbisInfo.channels;
	const auto rate = vorbisInfo.rate;

	if (vorbis_synthesis_init(&vorbisState, &vorbisInfo) != 0)
	{
		// 
		return {};
	}

	vorbis_block_init(&vorbisState, &vorbisBlock);

	bool endOfStream = false;

	while (!endOfStream)
	{
		readOggPageBuffer(resource, resourcedReaded, ogg);

		do {
			if (!readOggPacket(ogg))
				break;

			if (vorbis_synthesis(&vorbisBlock, &ogg.packet) == 0) /* test for success! */
                vorbis_synthesis_blockin(&vorbisState, &vorbisBlock);

			uint32_t samples = 0;
			float **pcm = nullptr;

			while((samples = vorbis_synthesis_pcmout(&vorbisState, &pcm)) > 0)
			{
				std::array<ogg_int16_t, initialConvSize> convBuffer;
				auto bout = std::min(samples, convSize);
				for(uint16_t channel = 0; channel < vorbisInfo.channels; ++channel)
				{
					float *mono = pcm[channel];
                    for(uint16_t sample = 0; sample < bout; ++sample)
					{
						auto val = static_cast<int32_t>(floor(mono[sample] * 32767.f + .5f));
						val = std::clamp(val, -32768, 32767);

						// interleaved format (see alBufferData)
						auto bufferIndex = static_cast<size_t>(sample * vorbisInfo.channels + channel);
						convBuffer[bufferIndex] = val;
					}
				}

				auto span = std::span<ogg_int16_t>(convBuffer.begin(), samples * vorbisInfo.channels);
				samplesBuffer.append_range(span);
				samplesOffset += samples * vorbisInfo.channels;

				vorbis_synthesis_read(&vorbisState, bout);
			}
		} while (!endOfStream);
		if (ogg_page_eos(&ogg.page))
			endOfStream = true;
	}

	vorbis_block_clear(&vorbisBlock);
    vorbis_dsp_clear(&vorbisState);

	ogg_stream_clear(&ogg.streamState);
    vorbis_comment_clear(&vorbisComment);
    vorbis_info_clear(&vorbisInfo);
	ogg_sync_clear(&ogg.syncState);
	
	if (channelsCount == 2)
		buffer->fillDataStereo(samplesBuffer.data(), samplesBuffer.size(), rate);
	else if (channelsCount == 1)
		buffer->fillDataMono(samplesBuffer.data(), samplesBuffer.size(), rate);
	else
		throw std::runtime_error("Unsupported channels count!");
	return buffer;
}

size_t readOggPageBuffer(std::shared_ptr<const IResource> resource, size_t &resourceOffset, OggInfo &info, bool pageIn)
{
	size_t readBytes = 0;

	while (ogg_sync_pageout(&info.syncState, &info.page) != 1)
	{
		auto syncTempBuffer = ogg_sync_buffer(&info.syncState, oggReadSize);
		readBytes =  resource->copyIn(syncTempBuffer, oggReadSize, resourceOffset);
		resourceOffset += readBytes;
		ogg_sync_wrote(&info.syncState, static_cast<long>(readBytes));
	}
	if (pageIn)
		ogg_stream_pagein(&info.streamState, &info.page);
	return readBytes;
}

bool readOggPacket(OggInfo &info)
{
	int packetResult = ogg_stream_packetout(&info.streamState, &info.packet);
	if (packetResult < 0)
		throw std::runtime_error("Packet corrupt?");
	return packetResult == 1;
}