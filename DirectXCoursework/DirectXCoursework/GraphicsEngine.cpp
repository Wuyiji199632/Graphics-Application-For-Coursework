
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include <d3dcompiler.h>

GraphicsEngine::GraphicsEngine()
{


}

bool GraphicsEngine::init()
{
	m_render_system = new RenderSystem();
	m_render_system->init();
	return true;
}

RenderSystem* GraphicsEngine::getRenderSystem()
{

	return m_render_system;
}

bool GraphicsEngine::release()
{
	m_render_system->release();
	delete m_render_system;
	return true;
}

GraphicsEngine::~GraphicsEngine()
{

}

GraphicsEngine* GraphicsEngine::get()
{
	static GraphicsEngine engine;
	return &engine;
}