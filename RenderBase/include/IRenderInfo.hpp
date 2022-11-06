#pragma once

#include <cstdint>
#include <string>
#include <memory>

#include <engine/IRenderEngine.hpp>
#include <ICore.hpp>
#include <info/IApplicationInfo.hpp>

namespace CubA4::render
{
	class IRenderInfo
	{
	public:
		virtual ~IRenderInfo() = default;
		virtual void init(std::shared_ptr<const info::IApplicationInfo> info, std::shared_ptr<const ICore> core) = 0;
		virtual void destroy() = 0;
		virtual std::string getRenderEngineId() const = 0;
		virtual std::shared_ptr<engine::IRenderEngine> getRenderEngine() = 0;
		virtual uint32_t getSDLWindowFlags() const = 0;
	protected:
		explicit IRenderInfo() = default;
	};
}
