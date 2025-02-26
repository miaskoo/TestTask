#pragma once
//INCLUDE

//Windows
#include <windows.h>

//classes cars
#include "sCar.h"
#include "sElectroCar.h"
#include "sGasEngine.h"
#include "sHybrid.h"

//файл тестового задания
#include "test_task.h"

//H
#include "main.h"
//END INCLUDE

//VARIBLE
const int MAX_CHARBUFF = 256;
int SCREEN_WIDTH = 1980;
int SCREEN_HEIGHT = 1024;
int sizeCarWidth = 200;
int sizeCarHeight = 200;
const int wmTimerTick = 40;//интервал между тиками таймера

extern std::vector<sCar*> pull_cars;//для доступа к пулу машинок - нужен для отрисовки

HINSTANCE hInst;                                // экземпляр окна
HWND hWND;
WCHAR szTitle[MAX_CHARBUFF]{ 'T' };                  // Буфер заголовка
WCHAR szWindowClass[MAX_CHARBUFF]{ 'N' };            // Буфер имени класса
//END VARIBLE

//FUNC
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//END FUNC



int APIENTRY wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{

	//INIT CLASS
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT2));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT2);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassExW(&wcex);
	//END INIT


    //CREATE
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
	//END CREATE


	//CODE
	if (Init_Pull() == false)//создали
		return 0;

	SetTimer(hWND, 0, wmTimerTick, NULL);//ставим таймер на окно
	//END CODE

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2));
    MSG msg;

    //Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

   hWND = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, SCREEN_WIDTH, SCREEN_HEIGHT, nullptr, nullptr, hInstance, nullptr);

   if (!hWND)
   {
      return FALSE;
   }

   ShowWindow(hWND, nCmdShow);
   UpdateWindow(hWND);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	}
	case WM_TIMER:
	{
		logic_tick();
		logic_tick();
		logic_tick();
		logic_tick();
		logic_tick();
		logic_tick();
		SendMessage(hWnd, WM_PAINT, NULL, NULL);
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		InvalidateRect(hWnd, NULL, TRUE);
		HDC hdc = BeginPaint(hWnd, &ps);
		for (auto car : pull_cars)
		{
			if (car->init == true)
			{
				Rectangle(hdc, car->rect.pos.x, car->rect.pos.y, car->rect.pos.x + car->rect.size.width, car->rect.pos.y + car->rect.size.height);
				auto get_type([=]() {if (car->dir == TOP) return L"UP"; if (car->dir == BOT) return L"DW"; if (car->dir == RIGHT) return L"RI"; return L"LE"; });
				auto text = LPCWSTR(get_type());
				TextOut(hdc, car->rect.pos.x, car->rect.pos.y, text, 3);
				int a = car->rect.pos.x;
				wchar_t str[20];
				_itow_s(a, str, 10); // Число, буфер, система счисления (десятичная) 
				TextOut(hdc, car->rect.pos.x+100, car->rect.pos.y, (std::wstring(L"x - ") + str).c_str(), 7);
				a = car->rect.pos.y;
				_itow_s(a, str, 10); // Число, буфер, система счисления (десятичная) 
				TextOut(hdc, car->rect.pos.x + 100, car->rect.pos.y+50, (std::wstring(L"y - ") + str).c_str(), 7);
			}
		}
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	default:
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	}
    return 0;
}
