#ifndef WORLD_HPP
#define WORLD_HPP

#include <world/IWorld.hpp>
#include <vector>

namespace CubA4
{
	namespace world
	{
		class World :
			public virtual CubA4::mod::world::IWorld
		{
		public:
			explicit World(std::shared_ptr<const CubA4::mod::world::IWorldDefinition> definition);
			~World();

			std::string getId() const override;
			std::wstring getName() const override;

			void subscribe(CubA4::mod::world::IWorldSubscriber *subscriber) override;
			void unsubscribe(CubA4::mod::world::IWorldSubscriber *subscriber) override;

			std::shared_ptr<const CubA4::mod::world::IWorldDefinition> getWorldDefinition() const override;
		protected:
		private:
			const std::shared_ptr<const CubA4::mod::world::IWorldDefinition> definition_;
			std::vector<CubA4::mod::world::IWorldSubscriber*> subscribers_;
		};
	}
}

#endif // WORLD_HPP
