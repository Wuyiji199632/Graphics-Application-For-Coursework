#include "MeshManager.h"

MeshManager::MeshManager()
{
}

MeshManager::~MeshManager()
{
}

MeshPtr MeshManager::createMeshFromFile(const wchar_t* file_path)
{
    return MeshPtr();
}

Resource* MeshManager::createResourceFromFileConcrete(const wchar_t* file_path)
{
    return nullptr;
}
