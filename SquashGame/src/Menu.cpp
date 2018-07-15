#include <Windows.h>
#include "screencasts.h"
#include <stdio.h>

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define GENERATE_BUTTON 4

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND);
void AddControls(HWND);
void LoadImages();

HMENU hMenu;
HWND hName, hAge, hOut, hLogo, hHand, hStart, hBut;
HBITMAP hLogoImage, hHandImage, hStartImage, hSubmitImage;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
	//MessageBox(NULL, "HELLO", "My First GUI", MB_OK);
	WNDCLASSW wc = { 0 };

	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = L"FirstScreenClass";
	wc.lpfnWndProc = WindowProcedure;

	if (!RegisterClassW(&wc))
		return -1;

	CreateWindowW(L"FirstScreenClass", L"Squash", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, windowWidth, windowHeight, NULL, NULL, NULL, NULL);
	MSG msg = { 0 };

	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_COMMAND:
		switch (wp) {
		case FILE_MENU_EXIT:
			DestroyWindow(hWnd);
;			break;
		case FILE_MENU_NEW:
			MessageBeep(MB_ICONINFORMATION);
			break;
		case GENERATE_BUTTON:
			//Criar métodos para gravar o nome capturado na BD;
			//Variavel: hName.
			//Linkar para a proxima janela que tenho que criar.
			MessageBox(NULL, "Missing the...", "Squash", MB_OK);
			//CreateWindowW(L"MyWindowClass", L"My Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, windowWidth, windowHeight, NULL, NULL, NULL, NULL);
			
			//Initiate the game?			
			break;
		}
		break;
	case WM_CREATE:
		//AddMenus(hWnd);
		LoadImages();
		AddControls(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}

void AddMenus(HWND hWnd) {
	hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	HMENU hSubMenu = CreateMenu();

	AppendMenu(hSubMenu, MF_STRING, NULL, "SubMenu Item");

	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, "New");
	//AppendMenu(hFileMenu, MF_STRING, FILE_MENU_OPEN, "Open");
	AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, "Open SubMenu");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL,NULL);
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Exit");

	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
	AppendMenu(hMenu, MF_STRING, NULL, "Help");

	SetMenu(hWnd, hMenu);
}

void AddControls(HWND hWnd) {
	hLogo = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, ((windowWidth / 2) - ((0.3*windowWidth) / 2)), 0, 0.3*windowWidth, 0.1*windowHeight, hWnd, NULL, NULL, NULL);

	hHand = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, ((windowWidth / 2) - ((0.1*windowWidth) / 2)), 0.1*windowHeight + 0.025*windowHeight, 0.1*windowWidth, 0.1*windowHeight, hWnd, NULL, NULL, NULL);
	
	//CreateWindowW(L"Static", L"Let's Start\nEnter Your Name below:", WS_VISIBLE | WS_CHILD | SS_CENTER, ((windowWidth/2)-((0.4*windowWidth)/2)), 0.32*windowHeight, 0.4*windowWidth, 0.1*windowHeight, hWnd, NULL, NULL, NULL);
	hStart = CreateWindowW(L"Static", L"Let's Start\nEnter Your Name below:", WS_VISIBLE | WS_CHILD | SS_BITMAP, ((windowWidth / 2) - ((0.3*windowWidth) / 2)), 0.32*windowHeight, 0.3*windowWidth, 0.1*windowHeight, hWnd, NULL, NULL, NULL);

	hName = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, ((windowWidth / 2) - (285 / 2)), 0.5*windowHeight - 0.05*windowHeight, 285, 0.05*windowHeight, hWnd, NULL, NULL, NULL);
	
	//CreateWindowW(L"Button", L"Submit", WS_VISIBLE | WS_CHILD, ((windowWidth / 2) - ((0.5*windowWidth) / 2)), 0.7*windowHeight, 0.5*windowWidth, 0.1*windowHeight, hWnd, (HMENU)GENERATE_BUTTON, NULL, NULL);
	hBut = CreateWindowW(L"Button", L"Submit", WS_VISIBLE | WS_CHILD | BS_BITMAP, ((windowWidth / 2) - (285 / 2)), 0.7*windowHeight, 285, 44, hWnd, (HMENU)GENERATE_BUTTON, NULL, NULL);
	SendMessageW(hBut, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hSubmitImage);

	SendMessageW(hLogo, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hLogoImage);
	SendMessageW(hHand, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hHandImage);
	SendMessageW(hStart, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hStartImage);
	
}

void LoadImages() {
	hLogoImage = (HBITMAP)LoadImageW(NULL, L"..\\SquashGame\\sq_logo.bmp", IMAGE_BITMAP, 164, 47, LR_LOADFROMFILE);
	hHandImage = (HBITMAP)LoadImageW(NULL, L"..\\SquashGame\\hand.bmp", IMAGE_BITMAP, 69, 73, LR_LOADFROMFILE);
	hStartImage = (HBITMAP)LoadImageW(NULL, L"..\\SquashGame\\start.bmp", IMAGE_BITMAP, 166, 25, LR_LOADFROMFILE);
	hSubmitImage = (HBITMAP)LoadImageW(NULL, L"..\\SquashGame\\submit.bmp", IMAGE_BITMAP, 285, 44, LR_LOADFROMFILE);
	
	if (hLogoImage == NULL || hHandImage == NULL || hStartImage == NULL || hSubmitImage == NULL) {
		MessageBox(NULL, "Não Carregou a imagem.", "Failed", MB_OK);
	}
}
