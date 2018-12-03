#ifndef IMATERIALBUILDER_HPP
#define IMATERIALBUILDER_HPP

#include <memory>

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace material
			{
				class IMaterial;

				class IMaterialBuilder
				{
				public:
					virtual std::shared_ptr<const IMaterial> build() = 0;
				protected:
					explicit IMaterialBuilder() = default;
					virtual ~IMaterialBuilder() = default;
				private:
				};
			}
		}
	}
}

#endif // IMATERIALBUILDER_HPP
