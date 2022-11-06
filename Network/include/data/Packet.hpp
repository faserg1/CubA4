#pragma once

#include "NetworkLibrary.hpp"
#include <cstdint>
#include <vector>

namespace CubA4::network::data
{
	enum class PacketType : unsigned char
	{
		RealTime,
		World,
		Info,
	};

	class LIBRARY_SHARED Packet
	{
	public:
		using byteArray = std::vector<unsigned char>;

		explicit Packet();
		~Packet();

		PacketType getType() const;
		void setType(PacketType type);
		uint64_t getSender() const;
		void setSender(uint64_t sender);
		uint64_t getReceiver() const;
		void setReceiver(uint64_t receiver);
		uint64_t getSendTime() const;
		void setSendTime(uint64_t sendTime);
		uint64_t getTimeToLive() const;
		void setTimeToLive(uint64_t timeToLive);
		const byteArray &getData() const;
		void setData(const byteArray &data);

		byteArray pack() const;
		static Packet unpack(const byteArray &data);
	protected:
		static constexpr std::size_t headerSize();
	private:
		PacketType type_;
		uint64_t sender_;
		uint64_t receiver_;
		uint64_t sendTime_;
		uint64_t timeToLive_;
		byteArray data_;
	};
}

