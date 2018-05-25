#ifndef IMOD_HPP
#define IMOD_HPP

#include <memory>

namespace CubA4
{
	namespace core
	{
		namespace logging
		{
			class ILogger;
		}
	}
	
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

			virtual void load(std::shared_ptr<core::logging::ILogger> logger) = 0;
			virtual void preinit() = 0;
			virtual void link(std::shared_ptr<const IModLinker> linker) = 0;
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