#pragma once

#include <memory>
#include <map>
#include <system/IAppClientCallback.hpp>
#include <system/IdentityMap.hpp>
#include <object/IObject.hpp>
#include <game/controller/IRootActions.hpp>

namespace CubA4::render
{
	class IRenderInfo;
}

namespace CubA4::render::engine
{
	class IRenderManager;
}

namespace CubA4::system
{
	class EnvironmentBuilderData
	{
	public:
		explicit EnvironmentBuilderData(const IAppClientCallback *appCallback, std::shared_ptr<CubA4::game::controller::IRootActions> actions);
		~EnvironmentBuilderData();

		const CubA4::render::IRenderInfo &getRenderInfo() const;
		std::shared_ptr<CubA4::render::engine::IRenderManager> getRenderManager() const;
		std::shared_ptr<CubA4::game::controller::IRootActions> getActions() const;
		IdentityMap &getIdentityMap();
		std::map<int64_t, std::shared_ptr<CubA4::object::IObject>> &getObjects();
	protected:
	private:
		const IAppClientCallback *appCallback_;
		const std::shared_ptr<CubA4::game::controller::IRootActions> actions_;
		IdentityMap identityMap_;
		std::map<int64_t, std::shared_ptr<CubA4::object::IObject>> objects_;
	};
}
