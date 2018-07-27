#ifndef TEMPLATE_HPP
#define TEMPLATE_HPP

#include <string>
#include <algorithm>
#include <array>
#include <stdexcept>

namespace CubA4
{	
	namespace util
	{
		template <class TValue>
		std::wstring to_string_(const TValue &value, const std::wstring &)
		{
			return std::to_wstring(value);
		}

		template <class TValue>
		std::string to_string_(const TValue &value, const std::string &)
		{
			return std::to_string(value);
		}

		std::string to_string_(const std::string &value, const std::string &)
		{
			return value;
		}

		std::wstring to_string_(const std::wstring &value, const std::wstring &)
		{
			return value;
		}

		std::string to_string_(const char *value, const std::string &)
		{
			return value;
		}

		std::wstring to_string_(const wchar_t *value, const std::wstring &)
		{
			return value;
		}

		template <class TChar, class TCharTraits = std::char_traits<TChar>, class TAllocator = std::allocator<TChar>, class ... TArgs>
		std::basic_string<TChar, TCharTraits, TAllocator> format(const std::basic_string<TChar, TCharTraits, TAllocator> &fmt, const TArgs &...args)
		{
			const auto searchCharacter = static_cast<TChar>('%');
			std::basic_string<TChar, TCharTraits, TAllocator> fmt_copy = fmt;
			size_t count = std::count(fmt.begin(), fmt.end(), searchCharacter);
			if (sizeof...(args) != count)
				throw std::runtime_error("format: invalid argument count or format string");
			if (count <= 0)
				return fmt;
			std::basic_string<TChar, TCharTraits, TAllocator>::iterator *iterators = new std::basic_string<TChar, TCharTraits, TAllocator>::iterator[count];
			size_t pos = 0, idx = 0;
			for (size_t idx = 0; idx < count; idx++)
			{
				pos = fmt.find(searchCharacter, pos);
				iterators[idx] = (fmt_copy.begin() + pos);
				pos++; //search from next pos if available
			}
			std::array<std::basic_string<TChar, TCharTraits, TAllocator>, sizeof...(args)> sArgs = { to_string_(args, fmt)... };
			for (idx = 0; idx < count; idx++)
			{
				fmt_copy.replace(iterators[idx], iterators[idx]+1, sArgs[idx]);
			}
			delete [] iterators;
			return fmt_copy;
		}

		template <class ... TArgs>
		std::string format(const char *fmt, const TArgs &...args)
		{
			return format(std::string(fmt), args...);
		}

		template <class ... TArgs>
		std::wstring format(const wchar_t *fmt, const TArgs &...args)
		{
			return format(std::wstring(fmt), args...);
		}
	}
}

#endif // TEMPLATE_HPP