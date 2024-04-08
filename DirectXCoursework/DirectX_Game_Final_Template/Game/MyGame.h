
#pragma once
#include <DX3D/AllHeaders.h>
#include<DX3D/Prerequisites.h>
#include <DX3D/Entity/Player.h>
#include <DX3D/Input/InputSystem.h>
#include<time.h>
class MyGame: public Game
{
public:
	MyGame();
	~MyGame();

protected:
	virtual void onStart();

	virtual void onUpdate(float deltaTime);

	float m_rotation;

private:
	Entity* m_entity=nullptr;
	float m_elapsedSeconds = 0;

	bool m_locked = true;
};

