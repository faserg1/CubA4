#pragma once

#include <core/IEnvironment.hpp>
#include <core/EnvironmentContext.hpp>

namespace CubA4::core
{
	class Environment :
		public virtual IEnvironment
	{
	public:
		explicit Environment(EnvironmentContext &&context);
		~Environment();

		int64_t getId(const std::shared_ptr<const CubA4::object::IObject> object) const override;
		int64_t getId(const CubA4::object::IObject *object) const override;
		std::string getIdName(const std::shared_ptr<const CubA4::object::IObject> object) const override;
		std::shared_ptr<const CubA4::object::IObject> getObject(int64_t id) const override;
		std::shared_ptr<const CubA4::object::IObject> getObject(const std::string &id) const override;
		std::shared_ptr<CubA4::object::IObject> getObject(int64_t id) override;
		std::shared_ptr<CubA4::object::IObject> getObject(const std::string &id) override;
	protected:
	private:
		const EnvironmentContext context_;
	};
}
