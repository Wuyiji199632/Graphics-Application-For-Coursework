#pragma once
#include "VertexShader.h"
#include "PixelShader.h"
#include "GraphicsEngine.h"
#include "ConstantBuffer.h"
#include <exception>
#include <vector>
class GraphicsEngine;
enum CULL_MODE
{
	CULL_MODE_FRONT = 0,
	CULL_MODE_BACK
};

class Material
{
public:
	Material(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path);
	~Material();

	void addTexture(const TexturePtr& texture);
	void removeTexture(unsigned int index);
	void setData(void* data, unsigned int size);
	void setCullMode(CULL_MODE mode);
	CULL_MODE getCullMode();

	VertexShaderPtr m_vertex_shader;
	PixelShaderPtr m_pixel_shader;
	std::vector<TexturePtr> m_vec_textures;
	ConstantBufferPtr m_constant_buffer;
	CULL_MODE m_cull_mode = CULL_MODE_BACK;
	friend class GraphicsEngine;
};

