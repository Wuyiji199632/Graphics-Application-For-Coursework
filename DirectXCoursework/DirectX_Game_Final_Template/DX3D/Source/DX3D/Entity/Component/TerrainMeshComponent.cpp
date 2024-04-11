#include <DX3D/Entity/Component/TerrainMeshComponent.h>


TerrainMeshComponent::TerrainMeshComponent()
{
}

TerrainMeshComponent::~TerrainMeshComponent()
{
	m_entity->getWorld()->getGame()->getGraphicsEngine()->removeComponent(this);
}

void TerrainMeshComponent::setHeightMap(const TexturePtr& heightMap)
{
	heightMapTexture = heightMap;
}

const TexturePtr& TerrainMeshComponent::getHeightMap()
{
	return heightMapTexture;
}

void TerrainMeshComponent::setGroundMap(const TexturePtr& groundMap)
{
	m_groundMap = groundMap;
}

const TexturePtr& TerrainMeshComponent::getGroundMap()
{
	return m_groundMap;
}

void TerrainMeshComponent::setCliffMap(const TexturePtr& cliffMap)
{
	m_cliffMap = cliffMap;
}

const TexturePtr& TerrainMeshComponent::getCliffMap()
{
	return m_cliffMap;
}

void TerrainMeshComponent::setSize(Vector3D& size)
{
	m_size = size;
}

Vector3D TerrainMeshComponent::getSize()
{
	return m_size;
}

void TerrainMeshComponent::updateTerrainData(void* data, unsigned int size)
{
	auto renderSystem = m_entity->getWorld()->getGame()->getGraphicsEngine()->getRenderSystem();

	if (!m_meshCb) {

		m_meshCb = renderSystem->createConstantBuffer(data, size);
	}
	else {
		m_meshCb->update(renderSystem->getImmediateDeviceContext(),data);
	}
}

void TerrainMeshComponent::onCreateInternal()
{
	m_entity->getWorld()->getGame()->getGraphicsEngine()->addComponent(this);
	generateTerrainMesh();
}

void TerrainMeshComponent::generateTerrainMesh()
{
	const UINT w = 512; const UINT h = 512;
	const UINT ww = w - 1; const UINT hh = h - 1;

	auto i = 0;
	VertexMesh* terrainMeshVerticies = new VertexMesh[w * h];
	UINT* terrainMeshIndicies = new UINT[ww * hh * 6];

	for (unsigned int x = 0; x < w; x++) {

		for (unsigned int y = 0; y < h; y++) {

			terrainMeshVerticies[y * w + x] = { Vector3D((f32)x/(f32)ww,0,(f32)y/(f32)hh),Vector2D((f32)x/(f32)ww,(f32)y/(f32)hh),Vector3D(),Vector3D(),Vector3D()};

			if (x < ww && y < hh) {

				terrainMeshIndicies[i] = (y + 1) * w + (x);
				terrainMeshIndicies[i+1] = (y) * 4 + (x);
				terrainMeshIndicies[i+2] = (y) * 4 + (x+1);
				terrainMeshIndicies[i+3] = (y) * 4 + (x+1);
				terrainMeshIndicies[i+4] = (y + 1) * 4 + (x+1);
				terrainMeshIndicies[i+5] = (y + 1) * 4 + (x);
				i += 6;

			}
		}
		
	}

	auto renderSystem = m_entity->getWorld()->getGame()->getGraphicsEngine()->getRenderSystem();
	m_meshVb = renderSystem->createVertexBuffer(terrainMeshIndicies, sizeof(VertexMesh),w*h);
	m_meshIb = renderSystem->createIndexBuffer(terrainMeshIndicies, ww * hh * 6);

	m_vertexShader = renderSystem->createVertexShader(L"Assets/Shaders/TerrainShader.hlsl","vsmain");

	m_pixelShader = renderSystem->createPixelShader(L"Assets/Shaders/TerrainShader.hlsl", "psmain");

}
