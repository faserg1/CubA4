#pragma once

#include <memory>
#include <filesystem>
#include <resources/IResource.hpp>

namespace CubA4::resources
{
	class FilesystemResource :
		public virtual IResource
	{
	public:
		explicit FilesystemResource(std::filesystem::path fullPath, Path mountedPath);
		~FilesystemResource();

		std::string path() const override;
		bool exists() const override;
		uint64_t size() const override;
		std::pair<std::shared_ptr<void>, uint64_t> data() const override;
		size_t copyIn(void *data, size_t maxSize, size_t offset) const override;
		void save(const void *data, size_t size) override;
	protected:
	private:
		const std::filesystem::path fullPath_;
		const Path mountedPath_;
	};
}
