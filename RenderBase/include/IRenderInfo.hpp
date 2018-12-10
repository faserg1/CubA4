#ifndef RENDERBASE_IRENDER_INFO_HPP
#define RENDERBASE_IRENDER_INFO_HPP

#include <cstdint>
#include <string>
#include <memory>

namespace CubA4
{
	namespace core
	{
		class ICore;
		namespace info
		{
			class IApplicationInfo;
		}
	}

	namespace render
	{
		namespace engine
		{
			class IRenderEngine;
		}

		class IRenderInfo
		{
		public:
			virtual ~IRenderInfo() = default;
			virtual void init(std::shared_ptr<const core::info::IApplicationInfo> info, std::shared_ptr<const core::ICore> core) = 0;
			virtual void destroy() = 0;
			virtual std::string getRenderEngineId() const = 0;
			virtual std::shared_ptr<engine::IRenderEngine> getRenderEngine() = 0;
			virtual uint32_t getSDLWindowFlags() const = 0;
		protected:
			explicit IRenderInfo() = default;
		};
	}
}

#endif // RENDERBASE_IRENDER_INFO_HPP