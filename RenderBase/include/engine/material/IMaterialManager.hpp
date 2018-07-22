#ifndef IMATERIALMANAGER_HPP
#define IMATERIALMANAGER_HPP

#include <memory>

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace material
			{
				class IShaderFactory;
				class IMaterialLayoutSetFactory;

				class IMaterialManager
				{
				public:
					virtual ~IMaterialManager() {}

					std::shared_ptr<IShaderFactory> getShaderFactory();
					std::shared_ptr<IMaterialLayoutSetFactory> getMaterialLayoutSetFactory();
				protected:
					explicit IMaterialManager() {}
				private:
				};
			}
		}
	}
}

#endif // IMATERIALMANAGER_HPP
