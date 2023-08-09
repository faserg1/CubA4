#pragma once

#include <engine/model/IRenderModel.hpp>
#include <manager/IModRenderManager.hpp>
#include <map>
#include <string>
#include <memory>

namespace CubA4::manager
{
	class ModRenderManager : public virtual IModRenderManager
	{
	public:
		using ModelType = CubA4::render::engine::model::IRenderModel;
		ModRenderManager();

		void addModel(const std::string &id, std::shared_ptr<const ModelType> model);
		std::shared_ptr<const ModelType> getModel(const std::string &id) const;
	private:
		std::map<std::string, std::shared_ptr<const ModelType>> models_;
	};
}