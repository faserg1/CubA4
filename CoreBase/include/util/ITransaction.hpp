#pragma once

namespace CubA4::util
{
	class ITransaction
	{
	public:
		virtual ~ITransaction() = default;

		virtual void commit() = 0;
		virtual void rollback() = 0;
	protected:
		explicit ITransaction() = default;
	};
}
