#pragma once

#include <memory>
#include <bullet/btBulletDynamicsCommon.h>

namespace CubA4::render::engine
{
	class IRenderManager;

	namespace debug
	{
		class IRenderDebug;
		class IRenderDebugCollection;
	}
	
}

namespace CubA4::physics
{
	class DebugRender : public btIDebugDraw
	{
		struct Data;
	public:
		DebugRender(CubA4::render::engine::IRenderManager *renderManager = nullptr);
		~DebugRender();
		void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;

		void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override;

		void reportErrorWarning(const char* warningString) override;

		void draw3dText(const btVector3& location, const char* textString) override;

		void setDebugMode(int debugMode) override;

		int getDebugMode() const override;

		void clearLines() override;
		void flushLines() override;
	private:
		std::shared_ptr<CubA4::render::engine::debug::IRenderDebug> debugRender_;
		std::shared_ptr<CubA4::render::engine::debug::IRenderDebugCollection> collection_;

		std::unique_ptr<Data> data_;

		int debugMode_ = 0;
	};
}