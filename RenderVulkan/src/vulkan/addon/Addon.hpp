#ifndef ADDON_HPP 
#define ADDON_HPP 

#include <string>
#include <vector>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			namespace addon
			{
				enum class AddonType 
				{
					Instance,
					Device
				};

				class Addon
				{
				public:
					///Имена, необходимые в аддоне
					virtual std::vector<std::string> names() const = 0;
					virtual AddonType type() const = 0;
					bool available() const;

					std::string joinNames() const;
				protected:
					explicit Addon();
					~Addon();

					///Все имена определенного типа аддона
					virtual std::vector<std::string> allNames() const = 0;
				private:
				};
			}
		}
	}
}

#endif // ADDON_HPP
