#pragma once

#include <functional>
#include <memory>

namespace CubA4::network::io
{
	class Connection;

	class Listener
	{
	public:
		explicit Listener();
		virtual ~Listener();
		virtual void subscribe(std::function<void(std::shared_ptr<Connection>)> subscriber) = 0;
	protected:
	private:
	};
}

