#ifndef TESTBLOCK_HPP
#define TESTBLOCK_HPP

#include <object/IBlock.hpp>

namespace CubA4
{
	namespace mod
	{
		namespace block
		{
			class TestBlock :
				public virtual CubA4::mod::object::IBlock
			{
			public:
				explicit TestBlock(std::shared_ptr<const CubA4::render::engine::model::IRenderModel> renderModel,
					std::shared_ptr<const CubA4::render::engine::material::IMaterial> renderMaterial);
				~TestBlock();

				std::string getId() const override;
				std::wstring getName() const override;

				std::shared_ptr<const CubA4::render::engine::model::IRenderModel> getRenderModel() const override;
				std::shared_ptr<const CubA4::render::engine::material::IMaterial> getRenderMaterial() const override;
			protected:
			private:
				const std::shared_ptr<const CubA4::render::engine::model::IRenderModel> renderModel_;
				const std::shared_ptr<const CubA4::render::engine::material::IMaterial> renderMaterial_;
			};
		}
	}
}

#endif // TESTBLOCK_HPP
