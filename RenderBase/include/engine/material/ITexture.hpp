#ifndef RENDERBASE_ITEXTURE_HPP
#define RENDERBASE_ITEXTURE_HPP

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace material
			{
				class ITexture
				{
				public:
					virtual ~ITexture() = default;
				protected:
					explicit ITexture() = default;
				private:
				};
			}
		}
	}
}

#endif // RENDERBASE_ITEXTURE_HPP
