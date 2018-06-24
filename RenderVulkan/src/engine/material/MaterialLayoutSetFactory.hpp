#ifndef MATERIALLAYOUTSETFACTORY_HPP
#define MATERIALLAYOUTSETFACTORY_HPP

#include <engine/material/IMaterialLayoutSetFactory.hpp>

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace material
			{
				class MaterialLayoutSetFactory :
					public virtual IMaterialLayoutSetFactory
				{
				public:
					explicit MaterialLayoutSetFactory();
					~MaterialLayoutSetFactory();

					std::shared_ptr<IMaterialLayoutBuilder> createMaterialLayout() override;
					std::vector<std::shared_ptr<IMaterialLayout>> build() override;
				protected:
				private:
				};
			}
		}
	}
}

#endif // MATERIALLAYOUTSETFACTORY_HPP
