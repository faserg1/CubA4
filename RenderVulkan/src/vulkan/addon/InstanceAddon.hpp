#ifndef IINSTANCEADDON_HPP 
#define IINSTANCEADDON_HPP

#include <memory>
#include "Addon.hpp" 

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Instance; 
			class InstanceBuilder; 
			
			namespace addon
			{
				class InstanceAddon : 
					public Addon 
				{
				public:
					AddonType type() const override;
					virtual void init(std::shared_ptr<const Instance> instance) = 0;
					virtual void destroy(std::shared_ptr<const Instance> instance) = 0;
					virtual void added(InstanceBuilder &builder) = 0;
				protected:
					explicit InstanceAddon();
					virtual ~InstanceAddon();
				private:
				};
			}
		}
	}
}

#endif // IINSTANCEADDON_HPP 
