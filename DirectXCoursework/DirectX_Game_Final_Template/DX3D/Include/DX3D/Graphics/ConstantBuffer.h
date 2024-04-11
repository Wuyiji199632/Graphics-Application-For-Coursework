
#pragma once
#include <d3d11.h> 
#include <wrl.h>
#include <DX3D/Prerequisites.h>

class ConstantBuffer
{
public:
	ConstantBuffer(); ~ConstantBuffer();
	ConstantBuffer(void* buffer, UINT size_buffer,RenderSystem * system);
	void update(const DeviceContextPtr& context, void* buffer);
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;
	RenderSystem * m_system = nullptr;
private:
	friend class DeviceContext;
};