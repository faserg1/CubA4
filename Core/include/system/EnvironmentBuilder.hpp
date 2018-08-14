#ifndef ENVIRONMENTBUILDER_HPP
#define ENVIRONMENTBUILDER_HPP

#include <system/IEnvironmentBuilder.hpp>

namespace CubA4
{
	namespace core
	{
		namespace system
		{
			class EnvironmentBuilder :
				public virtual IEnvironmentBuilder
			{
			public:
				explicit EnvironmentBuilder();
				~EnvironmentBuilder();

				void registerModel(std::shared_ptr<const CubA4::core::model::IModel> model) override;
				void registerWorld(std::shared_ptr<const CubA4::mod::world::IWorld> world) override;
			protected:
			private:
			};
		}
	}
}

#endif // ENVIRONMENTBUILDER_HPP
