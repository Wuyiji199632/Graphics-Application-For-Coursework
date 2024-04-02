
#pragma once
#include <d3d11.h>
#include "Prerequisites.h"
class SwapChain
{
public:
	SwapChain(HWND hwnd, UINT width, UINT height, RenderSystem* system);
	//Initialize SwapChain for a window
	
	~SwapChain();
	void setFullScreen(bool fullscreen,unsigned int width, unsigned int height);
	bool present(bool vsync);
	void resize(unsigned int width, unsigned int height);
private:
	void reloadBuffers(unsigned int width,unsigned int height);
	
	
private:
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_rtv;
	ID3D11DepthStencilView* m_dsv=nullptr;
	RenderSystem* m_system = nullptr;
private:
	friend class DeviceContext;
};
