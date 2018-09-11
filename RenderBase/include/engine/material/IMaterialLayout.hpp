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
				protected:
					explicit IMaterialLayout() = default;
					virtual ~IMaterialLayout() = default;
				private:
				};
			}
		}
	}
}

#endif // IMATERIALLAYOUT_HPP
