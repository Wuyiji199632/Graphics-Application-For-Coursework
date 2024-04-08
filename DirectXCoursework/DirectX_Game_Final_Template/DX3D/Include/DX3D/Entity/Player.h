#pragma once
#include <DX3D/AllHeaders.h>
#include<DX3D/Input/InputSystem.h>
#include <DX3D/Entity/Entity.h>

class Player : public Entity
{
public:
	Player();
	virtual ~Player();

protected:
	virtual void onCreate();
	virtual void onUpdate(float deltaTime);

private:
	Entity* m_entity = nullptr;
	float m_elapsedSeconds = 0.0f;

	float m_forward = 0.0f;
	float m_rightward = 0.0f;

};

