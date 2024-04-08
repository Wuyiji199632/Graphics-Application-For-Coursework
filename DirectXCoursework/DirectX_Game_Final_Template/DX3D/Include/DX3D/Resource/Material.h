
#pragma once
#include <DX3D/Resource/Resource.h>
#include<DX3D/Prerequisites.h>
#include <vector>

enum CULL_MODE
{
	CULL_MODE_FRONT=0,
	CULL_MODE_BACK
};

class GraphicsEngine;
class Material: public Resource
{
public:
	Material(const wchar_t* path, ResourceManager* manager);
	Material(const MaterialPtr & material, ResourceManager* manager);

	void addTexture(const TexturePtr& texture);
	void removeTexture(unsigned int index);

	void setData(void * data, unsigned int size);

	void setCullMode(const CullMode& mode);
	CullMode getCullMode();

private:
	VertexShaderPtr m_vertex_shader;
	PixelShaderPtr m_pixel_shader;
	ConstantBufferPtr m_constant_buffer;
	std::vector<Texture2DPtr> m_vec_textures;
	CullMode m_cull_mode = CullMode::Back;
	friend class GraphicsEngine;
};

