#ifndef IMODRENDERMANAGER_HPP
#define IMODRENDERMANAGER_HPP

#include <memory>
#include <string>

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace model
			{
				class IRenderModel;
			}
		}
	}

	namespace mod
	{
		namespace manager
		{
			class IModRenderManager
			{
			public:
				virtual std::shared_ptr<const CubA4::render::engine::model::IRenderModel> getModel(const std::string &id) const = 0;
			protected:
				explicit IModRenderManager() = default;
				virtual ~IModRenderManager() = default;
			private:
			};
		}
	}
}

#endif // IMODRENDERMANAGER_HPP
