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
    const ui32 w = 512;//Width Terrain and amount of verties on the x
    const ui32 h = 512;//Height Terrain and amount of verties on the y

    const ui32 ww = w - 1; //number of quads on the x
    const ui32 hh = h - 1; //number of quads on the y


    VertexMesh* terrainMeshVertices = new VertexMesh[w * h];//Will hold the data fro each vertex
    ui32* terrainMeshIndices = new ui32[ww * hh * 6];//Total Amount of indices

    auto i = 0;
    for (ui32 x = 0; x < w; x++)
    {
        for (ui32 y = 0; y < h; y++)
        {
            terrainMeshVertices[y * w + x] = {
                Vector3D((f32)x / (f32)ww, 0,(f32)y / (f32)hh),
                Vector2D((f32)x / (f32)ww, (f32)y / (f32)hh),
                Vector3D(),
                Vector3D(),
                Vector3D()
            };

            if (x < ww && y < hh) // if x and y are less than w - 1
            {
                terrainMeshIndices[i + 0] = (y + 1) * w + (x);
                terrainMeshIndices[i + 1] = (y) * w + (x);
                terrainMeshIndices[i + 2] = (y) * w + (x + 1);

                terrainMeshIndices[i + 3] = (y)*w + (x + 1);
                terrainMeshIndices[i + 4] = (y + 1) * w + (x + 1);
                terrainMeshIndices[i + 5] = (y + 1) * w + (x);
                i += 6;
            }
        }
    }

    auto renderSytem = m_entity->getWorld()->getGame()->getGraphicsEngine()->getRenderSystem();
    m_meshVb = renderSytem->createVertexBuffer(terrainMeshVertices, sizeof(VertexMesh), w * h);
    m_meshIb = renderSytem->createIndexBuffer(terrainMeshIndices, ww * hh * 6);

    m_vertexShader = renderSytem->createVertexShader(L"Assets/Shaders/TerrainShader.hlsl", "vsmain");
    m_pixelShader = renderSytem->createPixelShader(L"Assets/Shaders/TerrainShader.hlsl", "psmain");

}
