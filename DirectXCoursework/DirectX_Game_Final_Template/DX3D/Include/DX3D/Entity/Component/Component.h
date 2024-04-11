#pragma once
#include<DX3D/Graphics/IndexBuffer.h>
#include<DX3D/Graphics/ConstantBuffer.h>
#include <DX3D/Prerequisites.h>
#include<DX3D/Graphics/RenderSystem.h>
class Component
{
public:
	Component();
	virtual ~Component();
	void release();

	Entity* getEntity();
protected:
	virtual void onCreateInternal();
protected:
	size_t m_typeId = 0;
	Entity* m_entity = nullptr;
private:
	friend class Entity;
};

