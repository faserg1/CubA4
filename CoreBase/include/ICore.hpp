#ifndef ICORE_HPP
#define ICORE_HPP

#include <memory>

namespace CubA4
{
	namespace core
	{
		namespace system
		{
			class IStartup;
		}

		namespace config
		{
			class IFilePaths;
			class ICoreConfig;
		}

		namespace logging
		{
			class ILogger;
		}

		class ICore
		{
		public:
			//�������, ���������� const, ����� �������� �����.
			//� �������� ICore ���������� ��� std::shared_ptr<const ICore>, �� ���� �������, ��� ����� �������� ������ ��� �������

			///�������� �������� ����
			virtual const std::shared_ptr<const config::IFilePaths> getPaths() const = 0;
			///�������� ������������ ����������
			virtual std::shared_ptr<config::ICoreConfig> getConfig() const = 0;
			///�������� ������
			virtual std::shared_ptr<logging::ILogger> getLogger() const = 0;

			//�������, �� ���������� const ����� �������� ������ ��������� ����������, ��� ���, ��� ICore �� ���������� �� ������������ ���������.
			//� �������, ����� std::shared_ptr<ICore> ����� �������� ��� �������

			///�������� ����� ������� ����������
			virtual std::shared_ptr<system::IStartup> getStartup() = 0;
		protected:
			virtual ~ICore() {}
			explicit ICore() {}
		};
	}
}

#endif // ICORE_HPP