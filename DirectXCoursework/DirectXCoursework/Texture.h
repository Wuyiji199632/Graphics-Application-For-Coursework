#pragma once
#include "Resource.h"
#include "GraphicsEngine.h"
#include <d3d11.h>
#include <DirectXTex.h>
class Texture:public Resource
{
public:
	Texture(const wchar_t* full_path);
	~Texture();
private:
	ID3D11Resource* m_texture = nullptr;
	ID3D11ShaderResourceView* m_shader_res_view = nullptr;
	ID3D11SamplerState* m_sampler_state = nullptr;

private:
	friend class DeviceContext;

};

