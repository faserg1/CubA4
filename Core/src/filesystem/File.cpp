#include "./File.hpp"
#include <boost/filesystem/fstream.hpp>
#include <functional>
using namespace CubA4::core::filesystem;

File::File(boost::filesystem::path path) :
	path_(path)
{
	
}

File::~File()
{
	
}

uint64_t File::size() const
{
	return static_cast<uint64_t>(boost::filesystem::file_size(path_));
}

std::shared_ptr<void> File::load() const
{
	const auto fSize = size();
	auto *data = new unsigned char[fSize];
	auto readed = loadIn(data, fSize, 0);
	if (readed != fSize)
	{
		delete [] data;
		// TODO: [OOKAMI] Throw exception here
		return {};
	}
	std::function<void(decltype(data))> deleter = [](void *ptr)
	{
		auto castedPtr = static_cast<decltype(data)>(ptr);
		delete [] castedPtr;
	};
	return std::shared_ptr<void>(data, deleter);
}

size_t File::loadIn(void *data, size_t maxSize, size_t offset) const
{
	const auto fSize = size();
	const auto readToEnd = fSize - offset;
	const auto toRead = (maxSize > readToEnd ? readToEnd : maxSize);
	boost::filesystem::ifstream reader(path_, std::ios_base::binary | std::ios_base::in);
	reader.seekg(offset, std::ios_base::beg);
	reader.read(static_cast<char*>(data), toRead);
	return toRead;
}

void File::save(void *data, size_t size)
{
	boost::filesystem::ofstream writer(path_, std::ios_base::binary | std::ios_base::out);
	writer.write(static_cast<char*>(data), size);
	writer.flush();
}