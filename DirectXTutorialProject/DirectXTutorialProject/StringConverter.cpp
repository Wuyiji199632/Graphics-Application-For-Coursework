#include "StringConverter.h"

std::wstring StringConverter::stringToWide(std::string str)
{
	std::wstring wide_string(str.begin(), str.end());
	return wide_string;
}
