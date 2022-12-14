#include <tools/SpinLock.hpp>
using namespace CubA4::render::tools;

SpinLock::SpinLockLocker::SpinLockLocker(SpinLock *lock) : 
    parent_(lock)
{
    while (parent_->locked_);
    parent_->locked_.store(true);
}

SpinLock::SpinLockLocker::~SpinLockLocker()
{
    parent_->locked_.store(false);
}

std::unique_ptr<SpinLock::SpinLockLocker> SpinLock::lock()
{
    return std::make_unique<SpinLockLocker>(this);
}