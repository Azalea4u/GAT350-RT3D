#pragma once
#include <string>

namespace nc
{
	class StringUtils
	{
	public:
		std::string ToUpper(std::string Uppercase);
		std::string ToLower(std::string Lowercase);

		bool IsEqualIgnoreCase(std::string str1, std::string str2);

		std::string CreateUnique(const std::string input);
		//std::string CreateUnique(std::string input) { return input; }
	};
}