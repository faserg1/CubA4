#include "VersionDependency.hpp"
using namespace CubA4::info;

VersionDependency::VersionDependency(const IVersion &required, const IVersion &prefered) :
	required_(required), prefered_(prefered)
{
	
}

VersionDependency::~VersionDependency()
{
	
}

const IVersion &VersionDependency::required() const
{
	return required_;
}

const IVersion &VersionDependency::prefered() const
{
	return prefered_;
}