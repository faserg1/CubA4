#ifndef IMATERIALLAYOUT_HPP
#define IMATERIALLAYOUT_HPP

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace material
			{
				/**
				\brief Описание материала
				\description Содержит в себе свойства материала (шейдеры, как рендерится и т.д)
				**/
				class IMaterialLayout
				{
				public:
					virtual bool transparentMode() = 0;
				protected:
					explicit IMaterialLayout() {}
					virtual ~IMaterialLayout() {}
				private:
				};
			}
		}
	}
}

#endif // IMATERIALLAYOUT_HPP
