#include <physics/DebugRender.hpp>
#include <engine/IRenderManager.hpp>
#include <engine/debug/IRenderDebug.hpp>
#include <engine/debug/IRenderDebugCollection.hpp>
#include <world/GlobalPosition.hpp>

using namespace CubA4::physics;

DebugRender::DebugRender(CubA4::render::engine::IRenderManager *renderManager) :
	debugRender_(renderManager ? renderManager->getDebug() : std::shared_ptr<CubA4::render::engine::debug::IRenderDebug>()),
	data_(std::make_unique<Data>())
{
	if (!debugRender_)
		return;
	collection_ = debugRender_->addCollection();
}

DebugRender::~DebugRender() = default;

struct DebugRender::Data
{
	Data()
	{
		lines.reserve(CubA4::world::ChunkCube * 10);
	}
	std::vector<CubA4::render::engine::debug::LineInfo> lines;
};

void DebugRender::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	using namespace CubA4::world;
	if (!collection_)
		return;
	GlobalPosition gFrom(BasePos<long double>(from.getX(), from.getY(), from.getZ())),
		gTo(BasePos<long double>(to.getX(), to.getY(), to.getZ()));

	auto chPosFrom = convertPos<float>(gFrom.chunkPos()) * ChunkSize;
	auto chPosTo = convertPos<float>(gTo.chunkPos()) * ChunkSize;

	BasePos<float> lineFrom = convertPos<float>(gFrom.blockPosition()) + gFrom.inBlockPos() + chPosFrom;
	BasePos<float> lineTo = convertPos<float>(gTo.blockPosition()) + gTo.inBlockPos() + chPosTo;
	CubA4::ColorRGB rgb {color.getX(), color.getY(), color.getZ()};
	data_->lines.emplace_back(lineFrom, lineTo, rgb, rgb);
}

void DebugRender::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{

}

void DebugRender::reportErrorWarning(const char* warningString)
{

}

void DebugRender::draw3dText(const btVector3& location, const char* textString)
{

}

void DebugRender::setDebugMode(int debugMode)
{
	debugMode_ = debugMode;
}

int DebugRender::getDebugMode() const
{
	return debugMode_;
}

void DebugRender::clearLines()
{
	collection_->clear();
	data_->lines.clear();
}

void DebugRender::flushLines()
{
	collection_->addLines({}, data_->lines);
}