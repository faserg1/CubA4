#pragma once

#include <object/IEntityFactory.hpp>
#include <manager/IModEntityManager.hpp>
#include <map>
#include <string>
#include <memory>

namespace CubA4::manager
{
	class ModEntityManager : public virtual IModEntityManager
	{
	public:
		explicit ModEntityManager();
		~ModEntityManager();

		void addEntityFactory(const std::string &id, std::shared_ptr<const CubA4::object::IEntityFactory> factory);
		std::shared_ptr<const CubA4::object::IEntityFactory> getEntityFactory(const std::string &id) const;
	private:
		std::map<std::string, std::shared_ptr<const CubA4::object::IEntityFactory>> entityFactories_;
	};
}
