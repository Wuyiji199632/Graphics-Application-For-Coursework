#pragma once
#include <string>
class Resource
{


protected:
public:
	Resource(const wchar_t* full_path);
	virtual ~Resource();
protected:
	std::wstring m_full_path;
};

