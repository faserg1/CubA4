#pragma once

#include <memory>

namespace CubA4::object
{
	class IEntityHandler;

	struct HandlerComponent
	{
		std::weak_ptr<IEntityHandler> handler;
	};
}