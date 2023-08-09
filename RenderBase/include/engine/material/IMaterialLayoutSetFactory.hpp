#pragma once

#include <memory>
#include <vector>

namespace CubA4::render::engine::material
{
	class IMaterialLayoutBuilder;
	class IMaterialLayout;

	/** \brief Фабрика набора IMaterialLayout
	* \description Создает набор описаний материала
	*/
	class IMaterialLayoutSetFactory
	{
	public:
		
		virtual std::shared_ptr<IMaterialLayoutBuilder> createMaterialLayout() = 0;
		virtual std::vector<std::shared_ptr<const IMaterialLayout>> build() = 0;
	protected:
		explicit IMaterialLayoutSetFactory() = default;
		virtual ~IMaterialLayoutSetFactory() = default;
	private:
	};
}
