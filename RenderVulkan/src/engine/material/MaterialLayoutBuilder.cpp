#include "./MaterialLayoutBuilder.hpp"
#include <stdexcept>
#include <algorithm>
using namespace CubA4::render::engine::material;

MaterialLayoutBuilder::MaterialLayoutBuilder() :
	descriptorLayoutInfo_({}), transparentMode_(false)
{
	fillStartInfo();
}

MaterialLayoutBuilder::~MaterialLayoutBuilder()
{
	
}

void MaterialLayoutBuilder::setTransparentMode(bool transparent)
{
	transparentMode_ = transparent;
}

void MaterialLayoutBuilder::fillStartInfo()
{
	descriptorLayoutInfo_.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
}

void MaterialLayoutBuilder::prepare()
{
	//TODO: [OOKAMI] Переписать на приличный вид, когда состояний станет больше
	if (!transparentMode_)
	{
		bindings_.resize(1);
		bindings_[0].descriptorCount = 1;
		bindings_[0].descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
		bindings_[0].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
		bindings_[0].pImmutableSamplers = nullptr;
	}
	else
	{
		std::runtime_error("Реализация прозрачного режима отсутствует");
	}
	descriptorLayoutInfo_.bindingCount = bindings_.size();
	descriptorLayoutInfo_.pBindings = bindings_.data();
}

VkDescriptorSetLayoutCreateInfo &MaterialLayoutBuilder::getDescriptorLayoutInfo()
{
	return descriptorLayoutInfo_;
}