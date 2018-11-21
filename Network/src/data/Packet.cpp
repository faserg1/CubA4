#include "../include/data/Packet.hpp"
#include <string.h>
using namespace CubA4::network::data;

template <typename Type>
void copyAndMovePointer(void *&dst, Type value)
{
	constexpr size_t size = sizeof(Type);
	memcpy(dst, &value, size);
	dst = static_cast<unsigned char*>(dst) + size;
}

template <typename Type>
void readAndMovePointer(const void *&src, Type &value)
{
	constexpr size_t size = sizeof(Type);
	memcpy(&value, src, size);
	src = static_cast<const unsigned char*>(src) + size;
}

Packet::Packet()
{
	
}

Packet::~Packet()
{
	
}

PacketType Packet::getType() const
{
	return type_;
}

void Packet::setType(PacketType type)
{
	type_ = type;
}

uint64_t Packet::getSender() const
{
	return sender_;
}

void Packet::setSender(uint64_t sender)
{
	sender_ = sender;
}

uint64_t Packet::getReceiver() const
{
	return receiver_;
}

void Packet::setReceiver(uint64_t receiver)
{
	receiver_ = receiver;
}

uint64_t Packet::getSendTime() const
{
	return sendTime_;
}

void Packet::setSendTime(uint64_t sendTime)
{
	sendTime_ = sendTime;
}

uint64_t Packet::getTimeToLive() const
{
	return timeToLive_;
}

void Packet::setTimeToLive(uint64_t timeToLive)
{
	timeToLive_ = timeToLive;
}

const Packet::byteArray &Packet::getData() const
{
	return data_;
}

void Packet::setData(const Packet::byteArray &data)
{
	data_ = data;
}

Packet::byteArray Packet::pack() const
{
	Packet::byteArray packedData;
	packedData.resize(headerSize() + data_.size());
	void *ptr = packedData.data();
	copyAndMovePointer(ptr, type_);
	copyAndMovePointer(ptr, sender_);
	copyAndMovePointer(ptr, receiver_);
	copyAndMovePointer(ptr, sendTime_);
	copyAndMovePointer(ptr, timeToLive_);
	memcpy(ptr, data_.data(), data_.size());
	return std::move(packedData);
}

Packet Packet::unpack(const Packet::byteArray &data)
{
	Packet packet;
	const void *ptr = data.data();
	readAndMovePointer(ptr, packet.type_);
	readAndMovePointer(ptr, packet.sender_);
	readAndMovePointer(ptr, packet.receiver_);
	readAndMovePointer(ptr, packet.sendTime_);
	readAndMovePointer(ptr, packet.timeToLive_);
	packet.data_.resize(data.size() - headerSize());
	memcpy(packet.data_.data(), ptr, data.size() - headerSize());
	return std::move(packet);
}

constexpr size_t Packet::headerSize()
{
	return sizeof(type_) + sizeof(sender_) + sizeof(receiver_) + sizeof(sendTime_) + sizeof(timeToLive_);
}
