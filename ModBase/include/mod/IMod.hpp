#ifndef IMOD_HPP
#define IMOD_HPP

#include <memory>

namespace CubA4
{
	namespace core
	{
		namespace logging
		{
			class ILogger;
		}
	}
	
	namespace mod
	{
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

		class IMod
		{
		public:
			virtual ~IMod() {}

			//TODO: [OOKAMI] Replace with core
			virtual void load(std::shared_ptr<core::logging::ILogger> logger) = 0;
			virtual void preinit() = 0;
			virtual void link(std::shared_ptr<const IModLinker> linker) = 0;
			virtual void init() = 0;
			virtual void configure() = 0;
			virtual void done() = 0;

			virtual void preunload() = 0;
		protected:
			explicit IMod() {}
		};
	}
}

#endif // IMOD_HPP