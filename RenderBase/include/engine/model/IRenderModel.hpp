#ifndef RENDERBASE_IRENDERMODEL_HPP
#define RENDERBASE_IRENDERMODEL_HPP

#include <string>

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace model
			{
				class IRenderModel
				{
				public:
					virtual std::string getId() const = 0;
				protected:
					explicit IRenderModel() = default;
					virtual ~IRenderModel() = default;
				private:
				};
			}
		}
	}
}

#endif // RENDERBASE_IRENDERMODEL_HPP
