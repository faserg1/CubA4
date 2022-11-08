#pragma once

#include <config/IRenderConfig.hpp>
#include <memory>
#include <config/data/RenderData.hpp>

namespace CubA4::render::config
{
	class RenderConfig :
		public virtual IRenderConfig
	{
	public:
		explicit RenderConfig(std::string configsPath);
		~RenderConfig();

		std::tuple<unsigned, unsigned> getRenderResolution() const override;
		void setRenderResolution(std::tuple<unsigned, unsigned> res) override;

		std::string getPresentMethod() const override;
		void setPresentMethod(std::string method) override;

		int getLoggingLevel() const override;
		void setLoggingLevel(int lvl) override;

		void reload() override;
	protected:
	private:
		std::string native_config_path_;
		std::shared_ptr<RenderData> configTree_;
		void flushConfig();
	};
}
