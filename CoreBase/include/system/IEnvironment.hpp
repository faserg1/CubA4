#ifndef COREBASE_IENVIRONMENT_HPP
#define COREBASE_IENVIRONMENT_HPP

#include <cstdint>
#include <memory>
#include <string>

namespace CubA4
{
	namespace mod
	{
		namespace object
		{
			class IObject;
		}
	}

	namespace core
	{
		namespace system
		{
			class IEnvironment
			{
			public:
				virtual int64_t getId(const std::shared_ptr<const CubA4::mod::object::IObject> object) const = 0;
				virtual std::string getIdName(const std::shared_ptr<const CubA4::mod::object::IObject> object) const = 0;
				
				virtual std::shared_ptr<const CubA4::mod::object::IObject> getObject(int64_t id) const = 0;
				virtual std::shared_ptr<const CubA4::mod::object::IObject> getObject(const std::string &id) const = 0;

				template <class TObject>
				std::shared_ptr<const TObject> getObjectT(int64_t id) const
				{
					return std::dynamic_pointer_cast<const TObject>(getObject(id));
				}
				template <class TObject>
				std::shared_ptr<const TObject> getObjectT(const std::string &id) const
				{
					return std::dynamic_pointer_cast<const TObject>(getObject(id));
				}
			protected:
				explicit IEnvironment() = default;
				virtual ~IEnvironment() = default;
			private:
			};
		}
	}
}

#endif // COREBASE_IENVIRONMENT_HPP
