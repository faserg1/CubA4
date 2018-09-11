#ifndef ISHADERFACTORY_HPP
#define ISHADERFACTORY_HPP

#include <string>
#include <memory>
#include "IShader.hpp"

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace material
			{
				class IShaderFactory
				{
				public:
					virtual ~IShaderFactory() = default;

					/// \brief Создает Шейдер из бинарных данных (SPIR-V)
					/// \param data Бинарные данные шейдера на языке SPIR-V
					/// \param size Размер данных в байтах
					/// \param type Тип шейдера
					/// \param entryPoint точка входа шейдера
					/// \return Модуль шейдера
					virtual std::shared_ptr<IShader> createFromBinary(const void *data, size_t size, ShaderType type, std::string entryPoint) const = 0;
				protected:
					explicit IShaderFactory() = default;
				private:
				};
			}
		}
	}
}

#endif // ISHADERFACTORY_HPP
