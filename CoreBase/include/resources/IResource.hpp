#pragma once

#include <filesystem>
#include <utility>
#include <memory>

namespace CubA4
{
	namespace core
	{
		namespace resources
		{
			using Path = std::filesystem::path;	

			class IResource
			{
			public:
				/// Существует ли ресурс (в случае rw может отсутствовать)
				virtual bool exists() const = 0;
				/// Размер ресурса
				virtual uint64_t size() const = 0;
				/**
				\brief Возвращает данные ресурса (память выделяется заново)
				\return Указатель на память с ресурсом, размер в байтах
				*/
				virtual std::pair<std::shared_ptr<void>, uint64_t> data() const = 0;
				/**
				\brief Загружает ресурс в указанную память
				\param data Память, в которую нужно загрузить ресурс
				\param maxSize Максимальный размер
				\return Кол-во загруженных байт
				*/
				virtual size_t copyIn(void *data, size_t maxSize, size_t offset) const = 0;
				/**
				\brief Сохраняет данные в файл
				\param data Данные файла
				\param size Размер данных
				*/
				virtual void save(const void *data, size_t size) = 0;
			protected:
				explicit IResource() = default;
				virtual ~IResource() = default;
			private:
			};
		}
	}
}
