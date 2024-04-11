
#pragma once

#include <DX3D/Prerequisites.h>
#include <set>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/RenderSystem.h>
#include<DX3D/Entity/Component/MeshComponent.h>
#include<DX3D/Entity/Component/TransformComponent.h>
#include<DX3D/Entity/Component/CameraComponent.h>
#include<DX3D/Entity/Component/LightComponent.h>
#include <DX3D/Entity/Component/TerrainMeshComponent.h>
#include<DX3D/Entity/Entity.h>


struct MeshData
{
	MeshPtr mesh;
	MaterialPtr material;
};



class GraphicsEngine
{
public:
	//Initialize the GraphicsEngine and DirectX 11 Device
	GraphicsEngine(Game* game);
	//Release all the resources loaded
	~GraphicsEngine();


	void update();
public:
	RenderSystem * getRenderSystem();

	void addComponent(Component* component);

	void removeComponent(Component* component);


private:
	std::unique_ptr<RenderSystem> m_render_system = nullptr;
	Game* m_game = nullptr;

	std::set<MeshComponent*> m_meshes;
	std::set<CameraComponent*> m_cameras;
	std::set<LightComponent*> m_lights;
	std::set<TerrainMeshComponent*> m_terrains;
};

