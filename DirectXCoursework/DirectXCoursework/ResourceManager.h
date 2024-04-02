#pragma once
#include <unordered_map>
#include <string>
#include "Prerequisites.h"
#include "Resource.h"
class ResourceManager
{
public:
	ResourceManager();
	virtual ~ResourceManager();

	ResourcePtr createResourceFromFile(const wchar_t* file_path);

private:
	std::unordered_map<std::wstring, ResourcePtr> m_map_resources;
protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path)=0;
};

