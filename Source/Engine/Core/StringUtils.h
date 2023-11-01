#pragma once
#include <string>

namespace nc
{
	class StringUtils
	{
	public:
		std::string ToUpper(const std::string Uppercase);
		std::string ToLower(const std::string Lowercase);

		bool IsEqualIgnoreCase(const std::string str1, std::string str2);

		std::string CreateUnique(const std::string input);
	};
}