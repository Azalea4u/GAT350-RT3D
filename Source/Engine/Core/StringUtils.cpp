#include "StringUtils.h"

namespace nc
{
	std::string ToUpper(const std::string string)
	{
		std::string temp = string;
		for (char& c : temp)
		{
			c = toupper(c);
		}
		return temp;
	}

	std::string ToLower(const std::string string)
	{
		std::string temp = string;
		for (char& c : temp)
		{
			c = tolower(c);
		}
		return temp;
	}

	bool IsEqualIgnoreCase(const std::string& str1, const std::string& str2)
	{

		std::string temp1 = ToLower(str1);
		std::string temp2 = ToLower(str2);

		return (temp1 == temp2);
	}

	// takes in a string an input and appends static unsigned integer to the end of the string
	std::string CreateUnique(const std::string input)
	{
		static uint32_t unique = 1;
 
		return input + std::to_string(unique++);
	}

	// return the number at the end of a string "name43" -> 43, if there are no digits return -1
	int GetTrailingNumber(const std::string& str)
	{
		// if the string is empty return -1
		if (str.empty()) return -1;

		// check from the end of the string for characters that are digits, add digits to a strNumber
		std::string strNumber;
		for (size_t i = str.size() - 1; i >= 0; i--)
		{
			if (isdigit(str[i]))
				strNumber += str[i];
			else
				break;
		}

		// convert strNumber to a number if not empty
		return (!strNumber.empty()) ? std::stoi(strNumber) : -1;
	}

	// remove any digit characters from the end of the string "name43" -> "name"
	std::string RemoveTrailingNumber(const std::string& str)
	{
		if (str.empty()) return "";

		// set result string to str parameter
		// start at the end of the string and remove any characters that are digits
		// if character is not a digit, then exit
		std::string result = str;
		for (size_t i = str.size() - 1; i >= 0; i--)
		{
			if (isdigit(str[i]))
				result.pop_back();
			else
				break;
		}
	}
}