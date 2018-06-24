#ifndef IMATERIALLAYOUTSETFACTORY_HPP
#define IMATERIALLAYOUTSETFACTORY_HPP

#include <memory>
#include <vector>

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace material
			{
				class IMaterialLayoutBuilder;
				class IMaterialLayout;

				/** \brief ������� ������ IMaterialLayout
				* \description ������� ����� �������� ���������
				*/
				class IMaterialLayoutSetFactory
				{
				public:
					virtual ~IMaterialLayoutSetFactory() {}
					virtual std::shared_ptr<IMaterialLayoutBuilder> createMaterialLayout() = 0;
					virtual std::vector<std::shared_ptr<IMaterialLayout>> build() = 0;
				protected:
					explicit IMaterialLayoutSetFactory() {}
				private:
				};
			}
		}
	}
}

#endif // IMATERIALLAYOUTSETFACTORY_HPP
