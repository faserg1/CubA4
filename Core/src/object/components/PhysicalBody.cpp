#include <object/components/PhysicalBody.hpp>
#include <object/components/Transform.hpp>
using namespace CubA4::object;

MotionState::MotionState(entt::registry &registry, entt::entity entity) :
	registry_(registry), entity_(entity)
{

}

void MotionState::getWorldTransform(btTransform& worldTrans) const
{
	const auto &transform = registry_.get<Transform>(entity_);
	auto pos = transform.position.globalPos<float>();
	worldTrans.setOrigin({pos.x, pos.y, pos.z});
}

void MotionState::setWorldTransform(const btTransform& worldTrans)
{
	registry_.patch<Transform>(entity_, [&worldTrans](Transform &transform)
	{
		auto origin = worldTrans.getOrigin();
		transform.position = CubA4::world::BasePos<long double>{origin.x(), origin.y(), origin.z()};
	});
}