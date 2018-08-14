#ifndef IENVIRONMENTBUILDER_HPP
#define IENVIRONMENTBUILDER_HPP

#include <memory>

namespace CubA4
{
	namespace mod
	{
		namespace world
		{
			class IWorld;
		}
	}

	namespace core
	{
		namespace model
		{
			class IModel;
		}

		namespace system
		{
			class IEnvironmentBuilder
			{
			public:
				virtual void registerModel(std::shared_ptr<const CubA4::core::model::IModel> model) = 0;
				virtual void registerWorld(std::shared_ptr<const CubA4::mod::world::IWorld> world) = 0;
			protected:
				explicit IEnvironmentBuilder() = default;
				virtual ~IEnvironmentBuilder() = default;
			private:
			};
		}
	}
}

#endif // IENVIRONMENTBUILDER_HPP
