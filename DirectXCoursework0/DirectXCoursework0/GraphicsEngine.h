
#pragma once
#include <d3d11.h>

#include "Prerequisites.h"
#include "RenderSystem.h"
#include "TextureManager.h"
class GraphicsEngine
{
public:
	GraphicsEngine();
	//Initialize the GraphicsEngine and DirectX 11 Device

	
	~GraphicsEngine();
public:
	RenderSystem* getRenderSystem();
	TextureManager* getTextureManager();
public:
	static GraphicsEngine* get();
public:
	
	static void create();
	static void release();
private:
	RenderSystem* m_render_system = nullptr;
	static GraphicsEngine* m_engine;
	TextureManager* m_tex_manager=nullptr;
};


