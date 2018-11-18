#ifndef ISTARTUP_HPP
#define ISTARTUP_HPP

namespace CubA4
{
	namespace mod
	{
		class IModLoader;
	}

	namespace core
	{
		namespace system
		{
			class IAppCallback;

			class IStartup
			{
			public:
				virtual void setup(IAppCallback &appCallback) = 0;
				virtual void unload() = 0;

				virtual void run() = 0;
				virtual void stop() = 0;
			protected:
				explicit IStartup() = default;
				virtual ~IStartup() = default;
			private:
			};
		}
	}
}

#endif // ISTARTUP_HPP
