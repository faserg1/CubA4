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
				explicit TestBlock();
				~TestBlock();

				std::string getId() const override;
				std::wstring getName() const override;

				std::shared_ptr<const CubA4::render::engine::model::IRenderModel> getRenderModel() const override;
			protected:
			private:
			};
		}
	}
}

#endif // TESTBLOCK_HPP
