
#include "AppWindow.h"
#include "BumpyMapping.h"
#include "SpaceShooterGame.h"
#include "FrameBufferDemo.h"
#include "MiniGame.h"
#include "InputSystem.h"


int main()
{

	try
	{
		GraphicsEngine::create();
		InputSystem::create();
	}
	catch (...) { return -1; }

	{
		try
		{
			FrameBufferDemo app;
			while (app.isRun());
		}
		catch (...) {
			InputSystem::release();
			GraphicsEngine::release();
			return -1;
		}
	}

	InputSystem::release();
	GraphicsEngine::release();

	return 0;
}