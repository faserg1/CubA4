#pragma once

#include <entt/entt.hpp>

namespace CubA4::object
{
	template <class ...ClassList>
	class RemoveFirst
	{
	public:
		static void remove(entt::registry &registry, entt::entity entity)
		{
			(registry.remove<ClassList>(entity), ...);
		}
	private:
		RemoveFirst() = delete;
		RemoveFirst(const RemoveFirst&) = delete;
	};

}