#include "./MaterialLayoutSetFactory.hpp"
#include "./MaterialLayoutBuilder.hpp"
#include <algorithm>
using namespace CubA4::render::engine::material;
using namespace CubA4::render::vulkan;

MaterialLayoutSetFactory::MaterialLayoutSetFactory(std::shared_ptr<const Device> device) :
	device_(device)
{
	
}

MaterialLayoutSetFactory::~MaterialLayoutSetFactory()
{
	
}

std::shared_ptr<IMaterialLayoutBuilder> MaterialLayoutSetFactory::createMaterialLayout()
{
	auto builder = std::make_shared<MaterialLayoutBuilder>();
	builders_.push_back(builder);
	return builder;
}

std::vector<std::shared_ptr<const IMaterialLayout>> MaterialLayoutSetFactory::build()
{
	std::vector<std::shared_ptr<const IMaterialLayout>> layouts;
	std::for_each(builders_.begin(), builders_.end(), [](std::shared_ptr<IMaterialLayoutBuilder> iBuilder)
	{
		auto builder = dynamic_cast<MaterialLayoutBuilder*>(&*iBuilder);
		builder->prepare();
		auto descriptorLayoutInfo = builder->getDescriptorLayoutInfo();
	});
	return layouts;
}