#ifndef IRENDERMODEL_HPP
#define IRENDERMODEL_HPP

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

#endif // IRENDERMODEL_HPP
