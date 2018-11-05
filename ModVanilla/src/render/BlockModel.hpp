#ifndef BLOCKMODEL_HPP
#define BLOCKMODEL_HPP

#include <model/IRenderModelDefinition.hpp>

namespace CubA4
{
	namespace mod
	{
		namespace render
		{
			class BlockModel : public virtual 
				CubA4::core::model::IRenderModelDefinition
			{
			public:
				explicit BlockModel();
				~BlockModel();

				std::string getId() const override;
				std::vector<CubA4::core::model::Vertex> getVertices() const override;
				std::vector<unsigned short> getFaceIndices() const override;
			protected:
			private:
				
			};
		}
	}
}

#endif // BLOCKMODEL_HPP
