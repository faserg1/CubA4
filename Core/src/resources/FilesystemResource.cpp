#include "./FilesystemResource.hpp"
#include <fstream>
#include <filesystem>
using namespace CubA4::resources;

FilesystemResource::FilesystemResource(std::filesystem::path fullPath) :
	fullPath_(fullPath)
{
	
}

FilesystemResource::~FilesystemResource()
{
	
}

bool FilesystemResource::exists() const
{
	return std::filesystem::exists(fullPath_) && std::filesystem::is_regular_file(fullPath_);
}

uint64_t FilesystemResource::size() const
{
	return std::filesystem::file_size(fullPath_);
}

std::pair<std::shared_ptr<void>, uint64_t> FilesystemResource::data() const
{
	const auto fileSize = size();
	if (!fileSize)
		return {};
	auto *buffer = new char[fileSize];
	copyIn(buffer, fileSize, 0);
	return std::make_pair(std::shared_ptr<void>(buffer, [](void *data){ delete [] reinterpret_cast<char *>(data); }), fileSize);
}

size_t FilesystemResource::copyIn(void *data, size_t maxSize, size_t offset) const
{
	std::ifstream inFile(fullPath_, std::ios::binary);
	if (!inFile.is_open())
		return 0; // TODO: [OOKAMI] Log?
	inFile.seekg(offset, std::ios_base::beg);
	inFile.read(reinterpret_cast<char*>(data), maxSize);
	return static_cast<size_t>(inFile.tellg()) - offset;
}

void FilesystemResource::save(const void *data, size_t size)
{
	auto parentPath = fullPath_.parent_path();
	if (!std::filesystem::exists(parentPath))
		std::filesystem::create_directories(parentPath);
	std::ofstream outFile(fullPath_, std::ios::binary);
	outFile.write(reinterpret_cast<const char*>(data), size);
}