#include "StringUtils.h"

namespace nc
{
	std::string StringUtils::ToUpper(std::string string)
	{
		std::string temp = string;
		for (char& c : temp)
		{
			c = toupper(c);
		}
		return temp;
	}

	std::string StringUtils::ToLower(std::string string)
	{
		std::string temp = string;
		for (char& c : temp)
		{
			c = tolower(c);
		}
		return temp;
	}

	bool StringUtils::IsEqualIgnoreCase(std::string str1, std::string str2)
	{
		std::string temp1 = ToLower(str1);
		std::string temp2 = ToLower(str2);

		return (temp1 == temp2);
	}

	// takes in a string an input and appends static unsigned integer to the end of the string
	std::string StringUtils::CreateUnique(const std::string input)
	{
		static uint32_t unique = 0;
 
		return input + std::to_string(unique++);
	}
}