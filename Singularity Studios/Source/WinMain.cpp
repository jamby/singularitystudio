/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// File:	�WinMain.cpp�
// Author: Keith Maggio (KM)
// Purpose: Windows setup
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




//	WinMain.cpp : Basic Windows Shell.
#include <windows.h>						//	Needed for Windows Applications.

//////////////////////////////////////////////////////////////////////////
//Make sure to do these BEFORE including vld.h
#define VLD_CONFIG_AGGREGATE_DUPLICATES		//Dont show duplicates of the same memory leak!
#define VLD_MAX_DATA_DUMP 0					//Dont show me confusing hex i dont understand.
#include <vld.h>//Visual Leak detector
//////////////////////////////////////////////////////////////////////////

#include "CGame.h"
#include <ctime>
//	These read the keyboard asynchronously
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

const char* CLASSNAME		= "BasicWindow";		//	Window Class Name.



const char* WINDOW_TITLE	= "Dominator";		//	Window Title.


const int	WINDOW_WIDTH	= 800;					//	Window Width.
const int	WINDOW_HEIGHT	= 600;					//	Window Height

const BOOL	WINDOWED		= true;				//	Windowed or Full screen. START OFF FULLSCREEN




LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//	This is the main message handler of the system.
	PAINTSTRUCT	ps;			//	Used in WM_PAINT.
	HDC			hdc;		//	Handle to a device context.

	//	What is the message 
	switch(msg)
	{
		case WM_CREATE: 
		{
			//	Do initialization here
			return(0);
		}
		break;

		case WM_PAINT:
		{
			//	Start painting
			hdc = BeginPaint(hWnd,&ps);

			//	End painting
			EndPaint(hWnd,&ps);
			return(0);
		}
		break;

		case WM_DESTROY: 
		{
			//	Kill the application			
			PostQuitMessage(0);
			return(0);
		}
		break;

		default:
		break;
	}

	//	Process any messages that we didn't take care of 
	return (DefWindowProc(hWnd, msg, wParam, lParam));
}

//////////////////////////
//		WinMain			//
//////////////////////////

int WINAPI WinMain(	HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX winClassEx;		//	This will hold the class we create.
	MSG		 msg;				//	Generic message.
	HWND	 hWnd;				//	Main Window Handle.

	//	First fill in the window class structure
	winClassEx.cbSize			= sizeof(winClassEx);
	winClassEx.style			= CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winClassEx.lpfnWndProc		= WindowProc;
	winClassEx.cbClsExtra		= 0;
	winClassEx.cbWndExtra		= 0;
	winClassEx.hInstance		= hInstance;
	winClassEx.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	winClassEx.hCursor			= LoadCursor(NULL, IDC_ARROW);
	winClassEx.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	winClassEx.lpszMenuName		= NULL; 
	winClassEx.lpszClassName	= CLASSNAME;
	winClassEx.hIconSm			= NULL;

	srand((unsigned int)time(0));

	//	Register the window class
	if (!RegisterClassEx(&winClassEx))
		return(0);

	// Setup window style flags
	DWORD dwWindowStyleFlags = WS_VISIBLE;

	if (WINDOWED)
	{
		SetCursorPos(WINDOW_WIDTH/2,WINDOW_HEIGHT/2);
		dwWindowStyleFlags |= WS_OVERLAPPEDWINDOW;
		ShowCursor(FALSE);
	}
	else
	{
		dwWindowStyleFlags |= WS_POPUP;
		ShowCursor(FALSE);	// Stop showing the mouse cursor
		
	}

	// Setup the desired client area size
	RECT rWindow;
	rWindow.left	= 0;
	rWindow.top		= 0;
	rWindow.right	= WINDOW_WIDTH;
	rWindow.bottom	= WINDOW_HEIGHT;

	// Get the dimensions of a window that will have a client rect that
	// will really be the resolution we're looking for.
	AdjustWindowRectEx(&rWindow, 
						dwWindowStyleFlags,
						(winClassEx.lpszMenuName) ? TRUE : FALSE, 
						WS_EX_APPWINDOW);
	
	// Calculate the width/height of that window's dimensions
	int windowWidth		= rWindow.right - rWindow.left;
	int windowHeight	= rWindow.bottom - rWindow.top;

	//	Create the window
	if (!(hWnd = CreateWindowEx(WS_EX_APPWINDOW,										//	Extended Style flags.
								CLASSNAME,												//	Class Name.
								WINDOW_TITLE,											//	Title of the Window.
								dwWindowStyleFlags,										//	Window Style Flags.
								(GetSystemMetrics(SM_CXSCREEN)/2) - (windowWidth/2),	//	Window Start Point (x, y). 
								(GetSystemMetrics(SM_CYSCREEN)/2) - (windowHeight/2),
								windowWidth,											//	Width of Window.
								windowHeight,											//	Height of Window.
								NULL,													//	Handle to parent.
								NULL,													//	Handle to menu.
								hInstance,												//	Application Instance.
								NULL)))													//	Creation params.
		return(0);

	CGame* pGame = CGame::GetInstance();

	pGame->Initialize(hWnd, hInstance, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOWED);

	//	Enter main event loop
	while (TRUE)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{ 
			//	Test if this is a quit
			if (msg.message == WM_QUIT)
				break;
		
			//	Translate any accelerator keys
			TranslateMessage(&msg);

			//	Send the message to the window proc
			DispatchMessage(&msg);
		}


		//	Put Game Logic Here.
		if (!pGame->Main())
			break;
	
	}

	pGame->Shutdown();

	//	Unregister the window class
	UnregisterClass(CLASSNAME, hInstance);

	//	Return to Windows like this.
	return (int)(msg.wParam);
}
