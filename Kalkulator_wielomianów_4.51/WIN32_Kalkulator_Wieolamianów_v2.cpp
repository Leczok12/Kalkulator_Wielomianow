#include <windows.h>
#include "menu.h"
#include "wyliczanie.h"
#include "superparabole.h"

#define Nr_Menu_pomoc 1
#define Nr_Menu_plik_wczytaj 2
#define Nr_Menu_plik_zapisz 3
#define Nr_Menu_plik_wyjscie 4
//stałe

float wersja = 4.51;
int sposob = 1;

HBRUSH pCzarny = CreateSolidBrush(RGB(0, 0, 0));
HBRUSH pSzary = CreateSolidBrush(RGB(45, 45, 45));
HDC hDC;
//kolory

Licz Llicz;
Licz dodatkowy_Llicz;
//wyliczanie.h

Super Ssuper;
//superparabole.h

MSG Msg;
//wiadomości

HWND hP_1;
HWND hP_2;
//przyciski hP_1 - zatwirdz, hP_2 - Licz

HWND statyczny;
HWND Wozor_edit_1;
HWND Wozor_edit_2;
HWND hXYList;
HWND text;
HWND hZero;
HWND linia;
//ststic box'y

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void AddMenu(HWND);
void starterPack(HWND);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	wc.style = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = (HICON)LoadImage(NULL, L"ikona.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS );
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 3);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"Main";
	wc.cbWndExtra = 0;
	wc.hIconSm = (HICON) LoadImage(NULL, L"ikona.ico",IMAGE_ICON,0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED);  //LoadIcon(NULL, IDI_INFORMATION);
	
	if (!RegisterClassEx(&wc))
	{
		return 1;
	};
	
	HWND hWnd;
	wstringstream nazwa(L"Kalkulator wielomianów ");
	wstringstream wersjas(L"");
	wstringstream nazwak(L"");
	wersjas << wersja;
	nazwak << nazwa.str() + wersjas.str();
	hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, L"Main", nazwak.str().c_str(), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX , CW_USEDEFAULT, CW_USEDEFAULT, 820, 580, NULL, NULL, hInstance, NULL);
	


	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	Llicz.rysowanie_okna(hWnd);

	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;

	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	MENU mMenu;
	switch (msg)
	{
	case WM_COMMAND:
		if ((HWND)lParam == hP_1)
		{
			if (sposob == 1)
			{
				Llicz.pobieranie_wzor(hwnd, Wozor_edit_1);
				Llicz.liczenie();
				Llicz.wypisywanieXYlista(hXYList);
				Llicz.zmazanie(hwnd);
				Llicz.rysowanie_okna(hwnd);
				Llicz.wzor_rys(hwnd);
				Llicz.wzor(Wozor_edit_1);
			}
			else if (sposob == 2)
			{
				Llicz.zmazanie(hwnd);
				Llicz.rysowanie_okna(hwnd);
				Llicz.pobieranie_wzor(hwnd, Wozor_edit_1);
				Llicz.liczenie();
				dodatkowy_Llicz.pobieranie_wzor(hwnd, Wozor_edit_2);
				dodatkowy_Llicz.liczenie();
				for (int i = 0; i < 450; i++)
				{
					Ssuper.liczenie(Llicz.wyniki[i], dodatkowy_Llicz.wyniki[i], i);
				};
				Ssuper.wypisywanieXYlista(hXYList);
				Ssuper.wzor_rys(hwnd);
			};
			
		}
		if ((HWND)lParam == hP_2)
		{
			if (sposob==1)
			{
				DestroyWindow(Wozor_edit_1);
				sposob = 2;
				SetWindowText(hP_2, L"W(x) = x");
				linia = CreateWindowEx(0, L"STATIC", L"----------------------------------------------------", WS_CHILD | WS_VISIBLE | SS_LEFT, 85, 19, 210, 10, hwnd, NULL, NULL, NULL);
				Wozor_edit_1 = CreateWindowEx(0, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_CENTER, 90, 5, 200, 20, hwnd, NULL, NULL, NULL);
				Wozor_edit_2 = CreateWindowEx(0, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_CENTER, 90, 31, 200, 20, hwnd, NULL, NULL, NULL);
			}
			else if(sposob==2)
			{
				DestroyWindow(Wozor_edit_1);
				DestroyWindow(Wozor_edit_2);
				DestroyWindow(linia);
				sposob = 1;
				SetWindowText(hP_2, L"W(x) = x/1");
				Wozor_edit_1 = CreateWindowEx(0, L"EDIT", NULL, WS_CHILD | WS_VISIBLE, 90, 20, 200, 20, hwnd, NULL, NULL, NULL);
			}
			else
			{
				sposob = 1;
				SetWindowText(hP_2, L"W(x) = x/1");
			}
		}
		switch (wParam)
		{
		case Nr_Menu_plik_wczytaj:
			mMenu.wczytywanie(hwnd);
			break;
		case Nr_Menu_plik_wyjscie:
			PostQuitMessage(0);
			break;
		case Nr_Menu_plik_zapisz:
			mMenu.zapisz();
			break;
		case Nr_Menu_pomoc:
			mMenu.pomoc(hwnd);
			break;
		}
		break;

	case WM_CTLCOLORSTATIC:
		{
			HWND hCtl = (HWND)lParam;
			hDC = (HDC)wParam;

			if (hCtl != hZero)
			{
				SetBkMode(hDC, TRANSPARENT);
				SetTextColor(hDC, RGB(0, 255, 0));
				return(LRESULT)pCzarny;
			}
			if (hCtl == hZero)
			{
				SetBkMode(hDC, TRANSPARENT);
				SetTextColor(hDC, RGB(255, 255, 0));
				return(LRESULT)pCzarny;
			}
		}
		break;
	case WM_CTLCOLOREDIT:
		hDC = (HDC)wParam;
		SetBkMode(hDC, TRANSPARENT);
		SetTextColor(hDC, RGB(0, 255, 0));
		return(LRESULT)pSzary;
		break;
	case WM_CTLCOLORLISTBOX:
		hDC = (HDC)wParam;
		SetBkMode(hDC, TRANSPARENT);
		SetTextColor(hDC, RGB(0, 150,255));
		return(LRESULT)pCzarny;
		break;

	case WM_CTLCOLORBTN:
		hDC = (HDC)wParam;
		SetBkMode(hDC, TRANSPARENT);
		SetTextColor(hDC, RGB(0, 255, 0));
		return(LRESULT)pCzarny;
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_CREATE:
		starterPack(hwnd);
		AddMenu(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}
void starterPack(HWND hwnd)
{
	statyczny = CreateWindowEx(0, L"STATIC", L"W(x) = ", WS_CHILD | WS_VISIBLE | SS_LEFT , 40, 20, 50, 20, hwnd, NULL, NULL, NULL);
	Wozor_edit_1 = CreateWindowEx(0, L"EDIT", NULL, WS_CHILD | WS_VISIBLE , 90, 20, 200, 20,hwnd, NULL, NULL, NULL);
	hP_1 = CreateWindowEx(0, L"BUTTON", L"Licz", WS_CHILD | WS_VISIBLE, 185, 60, 100, 60, hwnd, NULL, NULL, NULL);
	hP_2 = CreateWindowEx(0, L"BUTTON", L"W(x) = x/1", WS_CHILD | WS_VISIBLE, 45, 60, 100, 60, hwnd, NULL, NULL, NULL);
	hXYList = CreateWindowEx(WS_EX_CLIENTEDGE, L"LISTBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER  | WS_VSCROLL | SS_CENTER,40, 140, 249, 360, hwnd, NULL, NULL, NULL);
};	

void AddMenu(HWND hWnd)
{
	HMENU hMenu = CreateMenu();
	HMENU hPlikiMenu = CreateMenu();
	HMENU hAkcje = CreateMenu();

	AppendMenu(hAkcje, MF_STRING, Nr_Menu_plik_wczytaj, L"Wczytaj");
	AppendMenu(hAkcje, MF_STRING, Nr_Menu_plik_zapisz, L"Zapisz");

	AppendMenu(hPlikiMenu, MF_POPUP, (UINT_PTR)hAkcje, L"Akcje");
	AppendMenu(hPlikiMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hPlikiMenu, MF_STRING, Nr_Menu_plik_wyjscie, L"Wyjście");

	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hPlikiMenu, L"Plik");
	AppendMenu(hMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hMenu, MF_STRING, Nr_Menu_pomoc, L"Pomoc");

	SetMenu(hWnd, hMenu);
};
