#include "Version.hpp"
#include <sstream>
using namespace CubA4::core::info;

Version::Version(unsigned short major, unsigned short minor, unsigned short patch, int build, int rev) :
	major_(major), minor_(minor), patch_(patch), build_(build), revision_(rev)
{
	
}

Version::Version(const IVersion &v) :
	major_(v.major()), minor_(v.minor()), patch_(v.patch()), build_(v.build()), revision_(v.revision())
{

}

Version::~Version()
{
	
}

unsigned short Version::major() const
{
	return major_;
}

unsigned short Version::minor() const
{
	return minor_;
}

unsigned short Version::patch() const
{
	return patch_;
}

int Version::build() const
{
	return build_;
}

int Version::revision() const
{
	return revision_;
}

std::string Version::to_string() const
{
	std::stringstream ss;
	ss << major_ << "." << minor_ << "." << patch_ << "." << build_ << "b" << revision_ << "r";
	std::string s;
	ss >> s;
	return s;
}