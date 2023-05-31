#pragma once

#include <system/IEnvironment.hpp>
#include <system/EnvironmentContext.hpp>

namespace CubA4::system
{
	class Environment :
		public virtual IEnvironment
	{
	public:
		explicit Environment(EnvironmentContext &&context);
		~Environment();

		int64_t getId(const std::shared_ptr<const CubA4::object::IObject> object) const override;
		std::string getIdName(const std::shared_ptr<const CubA4::object::IObject> object) const override;
		std::shared_ptr<const CubA4::object::IObject> getObject(int64_t id) const override;
		std::shared_ptr<const CubA4::object::IObject> getObject(const std::string &id) const override;
	protected:
	private:
		const EnvironmentContext context_;
	};
}
