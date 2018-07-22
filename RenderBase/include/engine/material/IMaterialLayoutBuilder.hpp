#ifndef IMATERIALLAYOUTBUILDER_HPP
#define IMATERIALLAYOUTBUILDER_HPP

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace material
			{
				///��������� �������� ���������
				class IMaterialLayoutBuilder
				{
				public:
					/// ������������� ����� ������������ ���������. �� ��������� �������� �����������
					virtual void setTransparentMode(bool transparent = true) = 0;
					// useShader()
					// addSampler()
					// add..*
				protected:
					explicit IMaterialLayoutBuilder() {}
					virtual ~IMaterialLayoutBuilder() {}
				private:
				};
			}
		}
	}
}

#endif // IMATERIALLAYOUTBUILDER_HPP
