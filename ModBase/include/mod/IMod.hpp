#pragma once

#include <memory>
#include <ICore.hpp>
#include <system/IEnvironmentBuilder.hpp>
#include <manager/IModManager.hpp>
#include <game/IGameControl.hpp>

namespace CubA4::mod
{
	enum class ModState : char
	{
		NotLoaded, ///< Найден, не загружен
		Preloaded, ///< Известна информация о моде, а также получен интерфейс мода
		Preinitializted, ///< Мод загрузил минимально необходимые ресурсы
		Linked, ///< Мод получил необходимые ему интрфейсы других модов.
		Inited, ///< Мод инициализирован, но не сконфигурирован
		Configurated, ///< Мод сконфигурирован
		PreFinish, ///< Мод проверил своё состояние и подготоваливается к запуску
		Loaded, ///< Мод готов к использованию
		Preunloaded, ///< Мод подготовлен к выгрузке, освободил все свои ресурсы
	};

	class IModLinker;
	class IModInfo;

	class IMod
	{
	public:
		virtual ~IMod() = default;

		virtual void load(std::shared_ptr<const ICore> core) = 0;
		virtual void preinit(std::shared_ptr<CubA4::system::IEnvironmentBuilder> builder) = 0;
		virtual void link(std::shared_ptr<const IModLinker> linker) = 0;
		virtual void init(std::shared_ptr<CubA4::system::IEnvironmentBuilder> builder) = 0;
		virtual void configure(std::shared_ptr<CubA4::system::IEnvironmentBuilder> builder) = 0;
		virtual void prefinish(std::shared_ptr<CubA4::system::IEnvironmentBuilder> builder) = 0;
		virtual void finish() = 0;

		virtual void start(CubA4::game::IGameControl &gameControl) = 0;
		virtual void stop() = 0;

		virtual void preunload() = 0;

		virtual const IModInfo &getInfo() const = 0;
		virtual std::weak_ptr<const CubA4::manager::IModManager> getManager() const = 0;
	protected:
		explicit IMod() = default;
	};
}
