// DirectXTutorialProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "ErrorLogger.h"
#include <d3d11.h>
#include <DirectXColors.h>
#include "SimpleMath.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"DirectXTK.lib")
// Include other DirectXTK headers as needed



int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {

    ErrorLogger::Log(S_OK, "Test Message");
    return 0;
}


