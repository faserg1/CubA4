#ifndef IMOD_HPP
#define IMOD_HPP

namespace CubA4
{
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

			virtual void load() = 0;
			virtual void preinit() = 0;
			virtual void link(const IModLinker *linker) = 0;
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