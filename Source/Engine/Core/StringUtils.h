#pragma once
#include <string>

namespace nc
{
	std::string ToLower(const std::string Lowercase);
	std::string ToUpper(const std::string Uppercase);

	bool IsEqualIgnoreCase(const std::string& str1, const std::string& str2);

	std::string CreateUnique(const std::string input);
}