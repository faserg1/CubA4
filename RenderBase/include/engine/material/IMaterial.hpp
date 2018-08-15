#ifndef IMATERIAL_HPP
#define IMATERIAL_HPP

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace material
			{
				/**
				\brief Материал.
				\description Можно сказать, применяет текстуры и т.д.
				**/
				class IMaterial
				{
				public:

				protected:
					explicit IMaterial() = default;
					virtual ~IMaterial() = default;
				private:
				};
			}
		}
	}
}

#endif // IMATERIAL_HPP
