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
	std::string StringUtils::CreateUnique(std::string input)
	{
		static unsigned int index = 0;
		std::string result = input + std::to_string(index++);
		
		return result;
	}
}