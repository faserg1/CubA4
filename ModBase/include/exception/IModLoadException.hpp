#ifndef MODLOADEXCEPTION_HPP
#define MODLOADEXCEPTION_HPP

#include "IModException.hpp"

namespace CubA4
{
	namespace exception
	{
		enum class ModState : char;

		class IModLoadException :
			public virtual IModException 
		{
		public:
			explicit IModLoadException() {}
			virtual ~IModLoadException() {}

			/// ���������� ����, � ������� ��������� ������
			virtual ModState getErrorState() const noexcept = 0;
		};
	}
}

#endif // MODLOADEXCEPTION_HPP