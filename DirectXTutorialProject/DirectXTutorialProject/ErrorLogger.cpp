#include "ErrorLogger.h"

#include <comdef.h>

void ErrorLogger::Log(std::string message)
{
	std::string error_message = "Error: " + message;
	MessageBoxA(NULL, error_message.c_str(), "Error", MB_ICONERROR);
}

void ErrorLogger::Log(HRESULT hr, std::string message)
{
	_com_error error(hr);
	error.ErrorMessage();
	std::wstring error_message = L"Error: " + StringConverter::stringToWide(message)+L"\n"+error.ErrorMessage();
	MessageBoxW(NULL, error_message.c_str(), L"Error", MB_ICONERROR);

}
