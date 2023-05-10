#pragma once

#include <memory>
#include <vulkan/vulkan.h>
#include <vector>
#include <vulkan/util/VulkanHandlerContainer.hpp>
#include <config/VulkanConfigAdapter.hpp>

namespace CubA4::render
{
    namespace engine
    {
        namespace material
        {
            class IShader;
        }
    }

    namespace vulkan
    {
        class Device;

        class Pipeline;
        struct PipelineInfo;

        class PipelineBuilderBase
        {
        public:
            explicit PipelineBuilderBase(std::shared_ptr<const Device> device, CubA4::render::config::VulkanConfigAdapter config);
            ~PipelineBuilderBase();

            void useShader(std::shared_ptr<const engine::material::IShader> shader);
            void addBuiltInDescriptorSetLayout(sVkDescriptorSetLayout builtInLayout);

            VkGraphicsPipelineCreateInfo build();
            void fillPipelineInfo(PipelineInfo &pipelineInfo) const;
        protected:
            const std::shared_ptr<const Device> device_;
            const CubA4::render::config::VulkanConfigAdapter config_;

            std::vector<VkVertexInputBindingDescription> vertexBindingDescriptions_;
            std::vector<VkVertexInputAttributeDescription> vertexAttrDescriptions_;

            VkPipelineVertexInputStateCreateInfo vertexInputInfo_ {};
            VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo_ {};
            VkPipelineRasterizationStateCreateInfo rasterizationInfo_ {};
            VkPipelineMultisampleStateCreateInfo multisampleInfo_ {};
            VkPipelineDepthStencilStateCreateInfo depthStencilInfo_ {};
            VkPipelineDynamicStateCreateInfo dynamicStateInfo_ {};
            VkPipelineViewportStateCreateInfo viewportStateInfo_{};
            VkPipelineColorBlendStateCreateInfo colorBlendInfo_{};

            std::vector<sVkDescriptorSetLayout> descriptorSetLayouts_;
            std::vector<VkPushConstantRange> pushConstantsRanges_;
            
        protected:
            virtual void prepareVertexInput() = 0;
            virtual void prepareInputAssembly();
            virtual void prepareRasterization();
            virtual void prepareMultisampling() = 0;
            virtual void prepareDepthStencil();
            virtual void prepareColorBlending() = 0;
            virtual void prepareDynmaic() = 0;
            virtual void prepareViewport() = 0;

            virtual void prepareDescriptorSets() = 0;
            virtual void preparePushConstants() = 0;
        private:
            VkPipelineLayout pipelineLayout_;

            std::vector<std::shared_ptr<const engine::material::IShader>> shaders_;

            VkSpecializationInfo vertexShaderSpec_;
            std::vector<VkSpecializationMapEntry> vertexShaderSpecEntries_;
            std::vector<unsigned char> vertexShaderSpecData_;

            std::vector<VkPipelineShaderStageCreateInfo> stages_;
        private:
            void prepareStages();
            void fillDefaults();
        };
    }
}

