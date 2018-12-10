#ifndef RENDERBASE_IMATERIALFACTORY_HPP
#define RENDERBASE_IMATERIALFACTORY_HPP

#include <memory>

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace material
			{
				class IMaterialBuilder;
				class IMaterialLayout;

				class IMaterialFactory
				{
				public:
					virtual std::shared_ptr<IMaterialBuilder> createMaterial(std::shared_ptr<const IMaterialLayout> layout) = 0;
				protected:
					explicit IMaterialFactory() = default;
					virtual ~IMaterialFactory() = default;
				private:
				};
			}
		}
	}
}

#endif // RENDERBASE_IMATERIALFACTORY_HPP
