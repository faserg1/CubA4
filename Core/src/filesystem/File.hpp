#ifndef CORE_FILE_HPP
#define CORE_FILE_HPP

#include <filesystem/IAbstractResource.hpp>
#include <boost/filesystem.hpp>

namespace CubA4
{
	namespace core
	{
		namespace filesystem
		{
			class File :
				public virtual IAbstractResource
			{
			public:
				explicit File(boost::filesystem::path path);
				~File();
				
				uint64_t size() const override;
				std::shared_ptr<void> load() const override;
				size_t loadIn(void *data, size_t maxSize, size_t offset) const override;
				void save(void *data, size_t size) override;
			protected:
			private:
				boost::filesystem::path path_;
			};
		}
	}
}

#endif // CORE_FILE_HPP
