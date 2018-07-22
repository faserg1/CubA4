#ifndef ISHADERFACTORY_HPP
#define ISHADERFACTORY_HPP

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
					virtual ~IShaderFactory() {}

					/// \brief ������� ������ �� �������� ������ (SPIR-V)
					/// \param data �������� ������ ������� �� ����� SPIR-V
					/// \param size ������ ������ � ������
					/// \param type ��� �������
					/// \return ������ �������
					virtual std::shared_ptr<IShader> createFromBinary(const void *data, size_t size, ShaderType type) const = 0;
				protected:
					explicit IShaderFactory() {}
				private:
				};
			}
		}
	}
}

#endif // ISHADERFACTORY_HPP
