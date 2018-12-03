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
				class IMaterialFactory;

				class IMaterialManager
				{
				public:
					virtual std::shared_ptr<IShaderFactory> getShaderFactory() const = 0;
					virtual std::shared_ptr<IMaterialLayoutSetFactory> getMaterialLayoutSetFactory() const = 0;
					virtual std::shared_ptr<IMaterialFactory> getMaterialFactory() const = 0;
				protected:
					explicit IMaterialManager() = default;
					virtual ~IMaterialManager() = default;
				private:
				};
			}
		}
	}
}

#endif // IMATERIALMANAGER_HPP
