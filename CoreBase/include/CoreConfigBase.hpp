#ifndef CORECONFIGBASE_HPP
#define CORECONFIGBASE_HPP

#include <string>

namespace CubA4
{
	namespace core
	{
		//Пока делаем простую реализацию
		class CoreConfigBase
		{
		public:
			virtual std::string getRenderEngineId() const = 0;
			virtual void setRenderEngineId(const std::string &renderEngineId) = 0;
			virtual std::string getMainFeatiresModId() const = 0;
			virtual void setMainFeaturesModId(const std::string &modId) = 0;

			virtual void reload() = 0;

			virtual ~CoreConfigBase() {}
		protected:
			explicit CoreConfigBase() {}
		};
	}
}

#endif // CORECONFIGBASE_HPP