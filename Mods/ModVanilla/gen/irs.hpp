#pragma once
#include <cstddef>

namespace CubA4
{
	namespace irs
	{
		/// \brief Получение внутренних файлов
		/// \param[in] name Путь к файлу
		/// \param[out] size Размер файла
		/// \return Указатель на начало файла, если файл найден. Иначе nullptr.
		const void *findFile(const char *name, std::size_t &size);
	}
}

