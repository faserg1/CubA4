#pragma once

#include <tuple>
#include <string>
#include <config/Enums.hpp>
namespace CubA4::render::config
{
	class IRenderConfig
	{
	public:
		virtual std::tuple<unsigned, unsigned> getRenderResolution() const = 0;
		virtual void setRenderResolution(std::tuple<unsigned, unsigned> res) = 0;

		virtual std::string getPresentMethod() const = 0;
		virtual void setPresentMethod(std::string method) = 0;

		virtual int getLoggingLevel() const = 0;
		virtual void setLoggingLevel(int lvl) = 0;

		virtual AntiAliasing getAntialiasing() const = 0;
		virtual void setAntialiasing(AntiAliasing lvl) = 0;

		virtual uint16_t getChunkDistance() const = 0;
		virtual void setChunkDistance(uint16_t distance) = 0;

		virtual void reload() = 0;
	protected:
		explicit IRenderConfig() = default;
		virtual ~IRenderConfig() = default;
	private:
	};
}
