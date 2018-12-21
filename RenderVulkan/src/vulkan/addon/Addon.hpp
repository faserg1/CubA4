#ifndef RENDERVULKAN_ADDON_HPP 
#define RENDERVULKAN_ADDON_HPP 

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
				/// Перечисление — тип аддона
				enum class AddonType 
				{
					/// На инстанс
					Instance,
					/// На устройство
					Device
				};

				class Addon
				{
				public:
					/// Имена, необходимые в аддоне
					virtual std::vector<std::string> names() const = 0;
					/// Тип аддона
					virtual AddonType type() const = 0;
					/// Доступен ли аддон
					bool available() const;

					std::string joinNames() const;
					std::string joinUnavailableNames() const;
				protected:
					explicit Addon();
					~Addon();

					/// Все имена определенного типа аддона
					virtual std::vector<std::string> allNames() const = 0;
					/// Проверяет указанные имена аддонов на доступность
					bool checkNames(std::vector<std::string> required) const;
				private:
				};
			}
		}
	}
}

#endif // RENDERVULKAN_ADDON_HPP
