#ifndef IMOD_HPP
#define IMOD_HPP

#include <memory>

namespace CubA4
{
	namespace core
	{
		class ICore;

		namespace system
		{
			class IEnvironmentBuilder;
		}
	}
	
	namespace mod
	{
		namespace manager
		{
			class IModManager;
		}

		enum class ModState : char
		{
			NotLoaded, ///< Найден, не загружен
			Preloaded, ///< Известна информация о моде, а также получен интерфейс мода
			Preinitializted, ///< Мод загрузил минимально необходимые ресурсы
			Linked, ///< Мод получил необходимые ему интрфейсы других модов.
			Inited, ///< Мод инициализирован, но не сконфигурирован
			Configurated, ///< Мод сконфигурирован
			Done, ///< Мод проверил своё состояние и готов к использованию
			Preunloaded, ///< Мод подготовлен к выгрузке, освободил все свои ресурсы
		};

		class IModLinker;
		class IModInfo;

		class IMod
		{
		public:
			virtual ~IMod() = default;

			virtual void load(std::shared_ptr<const core::ICore> core) = 0;
			virtual void preinit(std::shared_ptr<CubA4::core::system::IEnvironmentBuilder> builder) = 0;
			virtual void link(std::shared_ptr<const IModLinker> linker) = 0;
			virtual void init(std::shared_ptr<CubA4::core::system::IEnvironmentBuilder> builder) = 0;
			virtual void configure(std::shared_ptr<CubA4::core::system::IEnvironmentBuilder> builder) = 0;
			virtual void done(std::shared_ptr<CubA4::core::system::IEnvironmentBuilder> builder) = 0;

			virtual void preunload() = 0;

			virtual const IModInfo &getInfo() const = 0;
			virtual std::weak_ptr<const manager::IModManager> getManager() const = 0;
		protected:
			explicit IMod() = default;
		};
	}
}

#endif // IMOD_HPP