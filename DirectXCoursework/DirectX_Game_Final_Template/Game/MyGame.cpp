
#include "MyGame.h"
#include<DX3D/AllHeaders.h>
#include <DX3D/Entity/Player.h>
#include <time.h>

MyGame::MyGame()
{
	
}

MyGame::~MyGame()
{
}

void MyGame::onStart()
{
	Game::onStart();

	srand((unsigned int)time(nullptr));


	auto sphere = getResourceManager()->createResourceFromFile<Mesh>(L"Assets/Meshes/sphere.obj");

	auto sky = getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/sky.jpg");
	auto heightMap = getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/height_map.png");
	auto grass = getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/grass.jpg");
	auto ground = getResourceManager()->createResourceFromFile<Texture>(L"Assets/Textures/ground.jpg");


	auto skyMat = getResourceManager()->createResourceFromFile<Material>(L"Assets/Shaders/SkyBox.hlsl");
	skyMat->addTexture(sky);
	skyMat->setCullMode(CullMode::Front);

	//skybox
	{
		auto entity = getWorld()->createEntity<Entity>();
		auto meshComponent = entity->createComponent<MeshComponent>();
		auto transform = entity->getTransform();
		meshComponent->setMesh(sphere);
		meshComponent->addMaterial(skyMat);

		transform->setScale(Vector3D(5000, 5000, 5000));
	}

	//terrain
	{
		auto entity = getWorld()->createEntity<Entity>();
		auto terrainComponent = entity->createComponent<TerrainMeshComponent>();
		terrainComponent->setHeightMap(heightMap);
		terrainComponent->setGroundMap(grass);
		terrainComponent->setCliffMap(ground);

		auto transform = entity->getTransform();
		transform->setScale(Vector3D(1, 1, 1));
	}




	//light
	{
		m_entity = getWorld()->createEntity<Entity>();
		auto lightComponent = m_entity->createComponent<LightComponent>();
		lightComponent->setColor(Vector4D(1, 1, 1, 1));
		m_entity->getTransform()->setRotation(Vector3D(-0.707f, 0.707f, 0));
	}

	getWorld()->createEntity<Player>();


	getInputSystem()->lockCursor(m_locked);
}

void MyGame::onUpdate(float deltaTime)
{
	Game::onUpdate(deltaTime);
	m_rotation += 1.57f * deltaTime;

	m_entity->getTransform()->setRotation(Vector3D(-0.71f, m_rotation, 0));


	if (getInputSystem()->isKeyUp(Key::Escape))
	{
		m_locked = !m_locked;
		getInputSystem()->lockCursor(m_locked);
	}
	

}
