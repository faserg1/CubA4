#ifndef IMATERIALFACTORY_HPP
#define IMATERIALFACTORY_HPP

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			class IMaterialFactory
			{
			public:
				virtual ~IMaterialFactory() {}
			protected:
				explicit IMaterialFactory() {}
			private:
			};
		}
	}
}

#endif // IMATERIALFACTORY_HPP
