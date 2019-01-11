#ifndef COREBASE_IABSTRACTRESOURCE_HPP
#define COREBASE_IABSTRACTRESOURCE_HPP

#include <memory>

namespace CubA4
{
	namespace core
	{
		namespace filesystem
		{
			class IAbstractResource
			{
			public:
				/// Размер ресурса
				virtual uint64_t size() const = 0;
				/**
				\brief Возвращает данные ресурса (память выделяется заново)
				\return Указатель на память с ресурсом
				*/
				virtual std::shared_ptr<void> load() const = 0;
				/**
				\brief Загружает ресурс в указанную память
				\param data Память, в которую нужно загрузить ресурс
				\param maxSize Максимальный размер
				\return Кол-во загруженных байт
				*/
				virtual size_t loadIn(void *data, size_t maxSize, size_t offset) const = 0;
				/**
				\brief Сохраняет данные в файл
				\param data Данные файла
				\param size Размер данных
				*/
				virtual void save(void *data, size_t size) = 0;
			protected:
				explicit IAbstractResource() = default;
				virtual ~IAbstractResource() = default;
			private:
			};
		}
	}
}

#endif // COREBASE_IABSTRACTRESOURCE_HPP
