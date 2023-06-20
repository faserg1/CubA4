#include "./FilesystemResourceProvider.hpp"
#include "./FilesystemResource.hpp"
using namespace CubA4::resources;

FilesystemResourceProvider::FilesystemResourceProvider(Path realPath) :
	basePath_(realPath)
{
	
}

FilesystemResourceProvider::~FilesystemResourceProvider()
{
	
}

void FilesystemResourceProvider::onMount(Path from)
{
	mountedTo_ = from;
}

void FilesystemResourceProvider::onUnMount()
{
	mountedTo_ = Path{};
}

bool FilesystemResourceProvider::exists(Path path) const 
{
	const auto fullPath = getFullPath(path);
	return std::filesystem::exists(fullPath) && std::filesystem::is_regular_file(fullPath);
}

std::shared_ptr<const IResource> FilesystemResourceProvider::find(Path path) const
{
	if (!exists(path))
		return {};
	return std::make_shared<const FilesystemResource>(getFullPath(path), mountedTo_ / path);
}

std::shared_ptr<IResource> FilesystemResourceProvider::edit(Path path) const
{
	return std::make_shared<FilesystemResource>(getFullPath(path), mountedTo_ / path);
}

Path FilesystemResourceProvider::getFullPath(Path path) const
{
	return basePath_ / path;
}
