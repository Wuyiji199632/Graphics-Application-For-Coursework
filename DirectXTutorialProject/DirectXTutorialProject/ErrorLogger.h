#pragma once
#include <Windows.h>
#include "StringConverter.h"



class ErrorLogger {

public:
	static void Log(std::string message);
	static void Log(HRESULT result, std::string message);
};