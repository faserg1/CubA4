#ifndef IMOD_HPP
#define IMOD_HPP

namespace CubA4
{
	namespace mod
	{
		enum class ModState : char
		{
			NotLoaded, ///< ������, �� ��������
			Preloaded, ///< �������� ���������� � ����, � ����� ������� ��������� ����
			Preinitializted, ///< ��� �������� ���������� ����������� �������
			Linked, ///< ��� ������� ����������� ��� ��������� ������ �����.
			Inited, ///< ��� ���������������, �� �� ���������������
			Configurated, ///< ��� ���������������
			Done, ///< ��� �������� ��� ��������� � ����� � �������������
			Preunloaded, ///< ��� ����������� � ��������, ��������� ��� ���� �������
		};

		class IModLinker;

		class IMod
		{
		public:
			virtual ~IMod() {}

			virtual void load() = 0;
			virtual void preinit() = 0;
			virtual void link(const IModLinker *linker) = 0;
			virtual void init() = 0;
			virtual void configure() = 0;
			virtual void done() = 0;

			virtual void preunload() = 0;
		protected:
			explicit IMod() {}
		};
	}
}

#endif // IMOD_HPP