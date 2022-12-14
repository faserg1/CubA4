#pragma once

#include <atomic>
#include <memory>

namespace CubA4::render::tools
{
	class SpinLock
	{
		friend struct SpinLockLocker;
		struct SpinLockLocker
		{
			explicit SpinLockLocker(SpinLock *lock);
			~SpinLockLocker();
		private:
			SpinLock *const parent_;
		};
	public:
		explicit SpinLock() = default;
		~SpinLock() = default;

		[[nodiscard]] std::unique_ptr<SpinLockLocker> lock();
	private:
		std::atomic_bool locked_;
	};
}
