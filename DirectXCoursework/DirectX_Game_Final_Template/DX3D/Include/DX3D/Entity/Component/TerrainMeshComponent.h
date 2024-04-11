#pragma once
#include<DX3D/Prerequisites.h>
#include<DX3D/Graphics/DeviceContext.h>
#include<DX3D/Entity/Entity.h>
#include<DX3D/Game/World.h>
#include<DX3D/Graphics/RenderSystem.h>
#include<DX3D/Graphics/VertexBuffer.h>
#include<DX3D/Graphics/IndexBuffer.h>
#include<DX3D/Graphics/ConstantBuffer.h>
#include<DX3D/Entity/Component/Component.h>
#include<DX3D/Math/Vector2D.h>
#include<DX3D/Math/Vector3D.h>
#include<DX3D/Math/Vector4D.h>
#include<DX3D/Graphics/GraphicsEngine.h>
#include<DX3D/Math/VertexMesh.h>


class TerrainMeshComponent:public Component
{
public:
	TerrainMeshComponent();
	virtual~TerrainMeshComponent();

	void setHeightMap(const TexturePtr& heightMap);
	const TexturePtr& getHeightMap();

	void setGroundMap(const TexturePtr& groundMap);
	const TexturePtr& getGroundMap();

	void setCliffMap(const TexturePtr& cliffMap);
	const TexturePtr& getCliffMap();

	void setSize(Vector3D& size);
	Vector3D getSize();

	void updateTerrainData(void* data, unsigned int size);

protected:
	virtual void onCreateInternal();
private:
	TexturePtr heightMapTexture;
	TexturePtr m_groundMap;
	TexturePtr m_cliffMap;
	Vector3D m_size = Vector3D(512, 100, 512); //Specify the size of the terrain
private:
	void generateTerrainMesh();

	VertexBufferPtr m_meshVb;
	IndexBufferPtr m_meshIb;
	ConstantBufferPtr m_meshCb;

	VertexShaderPtr m_vertexShader;
	PixelShaderPtr m_pixelShader;

	friend class GraphicsEngine;
	friend class DeviceContext;
};

