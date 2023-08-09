#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <object/IObject.hpp>

namespace CubA4::system
{
	class IEnvironment
	{
	public:
		virtual int64_t getId(const std::shared_ptr<const CubA4::object::IObject> object) const = 0;
		virtual int64_t getId(const CubA4::object::IObject *object) const = 0;
		virtual std::string getIdName(const std::shared_ptr<const CubA4::object::IObject> object) const = 0;
		
		virtual std::shared_ptr<const CubA4::object::IObject> getObject(int64_t id) const = 0;
		virtual std::shared_ptr<const CubA4::object::IObject> getObject(const std::string &id) const = 0;

		virtual std::shared_ptr<CubA4::object::IObject> getObject(int64_t id) = 0;
		virtual std::shared_ptr<CubA4::object::IObject> getObject(const std::string &id) = 0;

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

		template <class TObject>
		std::shared_ptr<TObject> getObjectT(int64_t id)
		{
			return std::dynamic_pointer_cast<TObject>(getObject(id));
		}
		template <class TObject>
		std::shared_ptr<TObject> getObjectT(const std::string &id)
		{
			return std::dynamic_pointer_cast<TObject>(getObject(id));
		}
	protected:
		explicit IEnvironment() = default;
		virtual ~IEnvironment() = default;
	private:
	};
}
