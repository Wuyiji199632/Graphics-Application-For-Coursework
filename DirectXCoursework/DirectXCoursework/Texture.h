#pragma once
#include "Resource.h"
#include "GraphicsEngine.h"
#include <d3d11.h>
#include <DirectXTex.h>
#include "Rect.h"
class Texture:public Resource
{
public:
	enum Type {

		Normal=0,RenderTarget,DepthStencil
	};


public:
	Texture(const wchar_t* full_path);
	Texture(const Rect& size, Texture::Type type = RenderTarget);
	~Texture();

	Rect getSize();
	Texture::Type getType();
private:
	ID3D11Resource* m_texture = nullptr;
	ID3D11ShaderResourceView* m_shader_res_view = nullptr;
	ID3D11RenderTargetView* m_render_target_view = nullptr;
	ID3D11DepthStencilView* m_depth_stencil_view = nullptr;
	ID3D11SamplerState* m_sampler_state = nullptr;

	Texture::Type m_type = Texture::Type::Normal;
	Rect m_size;
	

private:
	friend class DeviceContext;

};

