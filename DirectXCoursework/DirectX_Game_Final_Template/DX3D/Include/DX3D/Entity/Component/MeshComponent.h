#pragma once

#include <DX3D/Prerequisites.h>
#include <DX3D/Entity/Entity.h>
#include <DX3D/Game/World.h>
#include <DX3D/Game/Game.h>
#include <DX3D/Entity/Component/Component.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include<vector>

class Component;
class MeshComponent:public Component
{
public:
	MeshComponent();
	~MeshComponent();


	void setMesh(const MeshPtr& mesh);

	const MeshPtr& getMesh();

	void addMaterial(const MaterialPtr&material);
	void removeMaterial(unsigned int index);
	const std::vector<MaterialPtr>& getMaterials();
protected:
	virtual void onCreateInternal() override;
private:
	MeshPtr m_mesh;
	std::vector<MaterialPtr> m_materials;
};

