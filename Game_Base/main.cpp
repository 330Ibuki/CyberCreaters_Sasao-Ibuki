//*********************************************
//
// メイン(main.cpp)
// Author : Junichi Uchiyama
//
//*********************************************

//インクルード
#include "main.h"
#include "renderer.h"
#include "manager.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int g_nCountFPS = 0;
CManager* g_pManager = nullptr;

int WINAPI WinMain(	_In_ HINSTANCE hInstance,
					_In_opt_ HINSTANCE hInstancePrev,
					_In_ LPSTR lpCmdLine,
					_In_ int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL, IDI_APPLICATION)
	};

	HWND hWnd;
	MSG msg;
	RECT rect = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
	DWORD dwCurrentTime;
	DWORD dwExecLastTime;
	DWORD dwFrameCount;
	DWORD dwFPSLastTime;

	RegisterClassEx(&wcex);

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	g_pManager = new CManager();

	if (FAILED(g_pManager->Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();


	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / GAME_FPS))
			{

				dwExecLastTime = dwCurrentTime;	

				g_pManager->Update();

				g_pManager->Draw();

				dwFrameCount++;
			}
		}
	}

	Uninit();

	timeEndPeriod(1);

	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	bool result = false;

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			result = (MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO | MB_ICONQUESTION) == IDYES);
			if (result == true)
			{
				DestroyWindow(hWnd);
			}
			break;
		}
		break;
	case WM_CLOSE:
		result = (MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO | MB_ICONQUESTION) == IDYES);
		if (result == true)
		{
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


void Uninit()
{
	g_pManager->Uninit();

	if (g_pManager != nullptr)
	{
		delete g_pManager;
		g_pManager = nullptr;
	}
}
