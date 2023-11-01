#pragma once
#include <string>

namespace nc
{
	class StringUtils
	{
	public:
		static std::string ToUpper(const std::string Uppercase);
		static std::string ToLower(const std::string Lowercase);

		static bool IsEqualIgnoreCase(const std::string str1, std::string str2);

		static std::string CreateUnique(const std::string input);
	};
}