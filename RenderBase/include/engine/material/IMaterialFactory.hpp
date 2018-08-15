#ifndef IMATERIALFACTORY_HPP
#define IMATERIALFACTORY_HPP

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace material
			{
				class IMaterialFactory
				{
				public:
					virtual ~IMaterialFactory() = default;
				protected:
					explicit IMaterialFactory() = default;
				private:
				};
			}
		}
	}
}

#endif // IMATERIALFACTORY_HPP
