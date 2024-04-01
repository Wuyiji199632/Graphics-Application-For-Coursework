
#pragma once
#include <Windows.h>



class Window
{
public:
	//Initialize the window
	Window();
	
	
	bool broadcast();
	//Release the window

	bool isRun();

	RECT getClientWindowRect();



	//EVENTS
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();
	virtual void onFocus();
	virtual void onKillFocus();

	~Window();
protected:
	HWND m_hwnd;
	bool m_is_run;
	bool m_is_init = false;
};

