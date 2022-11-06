#pragma once

#include "NetworkLibrary.hpp"
#include <functional>
#include <vector>
#include <memory>
#include <future>

namespace CubA4::network::io
{
	enum class ConnectionProtocol
	{
		TCP,
		UDP
	};

	class LIBRARY_SHARED Connection
	{
	public:
		using cReadFunc = std::function<void(std::shared_ptr<const std::string>)>;
		virtual ~Connection();

		virtual ConnectionProtocol protocol() = 0;
		virtual std::shared_future<void> send(const std::string &data) = 0;
		void subscribe(cReadFunc readFunc);
	protected:
		explicit Connection();
		void readed(std::shared_ptr<const std::string> data);
	private:
		std::vector<cReadFunc> subscribers_;
	};
}
