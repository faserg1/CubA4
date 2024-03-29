#pragma once

#include <memory>
#include <resources/IResource.hpp>
#include <model/RenderModelData.hpp>

namespace CubA4::model
{
	class IModelReader
	{
	public:
		virtual ~IModelReader() = default;
		virtual BlockRenderModelData readBlockRenderModel(std::shared_ptr<const resources::IResource> resource) const = 0;
		virtual void writeBlockRenderModel(std::shared_ptr<resources::IResource> resource, const BlockRenderModelData &model) = 0;

		virtual RenderModelData readRenderModel(std::shared_ptr<const resources::IResource> resource) const = 0;
		virtual void writeRenderModel(std::shared_ptr<resources::IResource> resource, const RenderModelData &model) = 0;
	protected:
		explicit IModelReader() = default;
	};
}
