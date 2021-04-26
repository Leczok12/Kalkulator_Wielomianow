#include <windows.h>
#include <fstream>**
#include "okno_wzor.h"
#include "menu.h"
#include "wyliczanie.h"
#include "superparabole.h"

#define Nr_Menu_pomoc 1
#define Nr_Menu_plik_wczytaj 2
#define Nr_Menu_plik_zapisz 3
#define Nr_Menu_plik_wyjscie 4
#define Nr_Menu_motyw_czerwony 10001
#define Nr_Menu_motyw_rozowy 10002
#define Nr_Menu_motyw_niebieski 10003
#define Nr_Menu_motyw_cyjan 10004
#define Nr_Menu_motyw_zielony 10005
#define Nr_Menu_motyw_zolty 10006


float wersja = 4.61;
double dodatkowa = 0;
int sposob = 1;
int R = 0;
int G = 255;
int B = 0;

HFONT hFont = CreateFont(18, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE, TEXT("Segoe UI Semibold"));

HBITMAP hHp_1;
HBITMAP hHp_2_1;
HBITMAP hHp_2_2;
//bitmapy przyciski

HBRUSH pCzarny = CreateSolidBrush(RGB(0, 0, 0));
HBRUSH pSzary = CreateSolidBrush(RGB(45, 45, 45));
HDC hDC;
//kolory

Licz Llicz;
Licz dodatkowy_Llicz;
//wyliczanie.h

Super Ssuper;
//superparabole.h

okno_rys Ookno;
//okno_wzor.h

MSG Msg;
//wiadomości

HWND hP_1;
HWND hP_2;
//przyciski hP_1 - zatwirdz, hP_2 - Licz

HWND statyczny;
HWND Wozor_edit_1;
HWND Wozor_edit_2;
HWND Wozor_edit_3;
HWND hXYList;
HWND text;
HWND linia;
//ststic box'y

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void zmiana_motywu(int, int, int, HWND);
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
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+3);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"Main";
	wc.cbWndExtra = 0;
	wc.hIconSm = (HICON)LoadImage(NULL, L"ikona.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED);
	
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

	fstream kolor;
	kolor.open("kolor.log", ios::in);
	if (kolor.good()==true)
	{
		kolor >> R;
		kolor >> G;
		kolor >> B;
	}
	else
	{
		MessageBox(hWnd, L"W kalkulatoże wielomianów", L"Witaj!", MB_OK);
	}
	kolor.close();
	
	zmiana_motywu(R, G, B, hWnd);

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
		Ookno.zmazanie(hwnd);
		Ookno.rys(hwnd, R, G, B);
	case WM_COMMAND:
		if ((HWND)lParam == hP_1)
		{
			if (sposob == 1)
			{
				Llicz.pobieranie_wzor(hwnd, Wozor_edit_1);
				Llicz.liczenie();
				Llicz.wypisywanieXYlista(hXYList);
				Ookno.zmazanie(hwnd);
				Ookno.rys(hwnd, R, G, B);
				Llicz.wzor_rys(hwnd);
				Llicz.wzor(Wozor_edit_1);
			}
			else if (sposob == 2)
			{
				Ookno.zmazanie(hwnd);
				Ookno.rys(hwnd, R, G, B);
				Llicz.pobieranie_wzor(hwnd, Wozor_edit_1);
				Llicz.liczenie();
				dodatkowy_Llicz.pobieranie_wzor(hwnd, Wozor_edit_2);
				dodatkowy_Llicz.liczenie();

				wchar_t x[200];
				GetWindowText(Wozor_edit_3,x, 200);

				dodatkowa = _wtof(x);
				
				for (int i = 0; i < 450; i++)
				{
					Ssuper.liczenie(Llicz.wyniki[i], dodatkowy_Llicz.wyniki[i], i,dodatkowa);
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
				SendMessage(hP_2, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hHp_2_2);
				linia = CreateWindowEx(0, L"STATIC", L"-------------------------------- +", WS_CHILD | WS_VISIBLE | SS_LEFT, 85, 19, 210, 14, hwnd, NULL, NULL, NULL);
				Wozor_edit_1 = CreateWindowEx(0, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_CENTER, 90, 5, 120, 20, hwnd, NULL, NULL, NULL);
				Wozor_edit_2 = CreateWindowEx(0, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_CENTER, 90, 31, 120, 20, hwnd, NULL, NULL, NULL);
				Wozor_edit_3 = CreateWindowEx(0, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_CENTER, 232, 18, 50, 20, hwnd, NULL, NULL, NULL);
			}
			else if(sposob==2)
			{
				DestroyWindow(Wozor_edit_1);
				DestroyWindow(Wozor_edit_2);
				DestroyWindow(Wozor_edit_3);
				DestroyWindow(linia);
				sposob = 1;
				SendMessage(hP_2, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hHp_2_1);
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
		case Nr_Menu_motyw_czerwony:
			zmiana_motywu(255, 0, 0,hwnd);
			break;
		case Nr_Menu_motyw_rozowy:
			zmiana_motywu(255, 0, 255, hwnd);
			break;
		case Nr_Menu_motyw_niebieski:
			zmiana_motywu(0, 0, 255, hwnd);
			break;
		case Nr_Menu_motyw_cyjan:
			zmiana_motywu(0, 255, 255, hwnd);
			break;
		case Nr_Menu_motyw_zielony:
			zmiana_motywu(0, 255, 0,hwnd);
			break;
		case Nr_Menu_motyw_zolty:
			zmiana_motywu(255, 255, 0,hwnd);
			break;
		}
		break;

	case WM_CTLCOLORSTATIC:
		//HWND hCtl = (HWND)lParam;
		hDC = (HDC)wParam;
		SetBkMode(hDC, TRANSPARENT);
		SetTextColor(hDC, RGB(R, G, B));
		return(LRESULT)pCzarny;
		break;
	case WM_CTLCOLOREDIT:
		hDC = (HDC)wParam;
		SetBkMode(hDC, TRANSPARENT);
		SetTextColor(hDC, RGB(R, G, B));
		return(LRESULT)pSzary;
		break;
	case WM_CTLCOLORLISTBOX:
		hDC = (HDC)wParam;
		SetBkMode(hDC, TRANSPARENT);
		SetTextColor(hDC, RGB(R, G, B));
		return(LRESULT)pCzarny;
		break;
	case WM_CTLCOLORBTN:
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
	Ookno.zmazanie(hwnd);
	Ookno.rys(hwnd, R, G, B);
	statyczny = CreateWindowEx(0, L"STATIC", L"W(x) = ", WS_CHILD | WS_VISIBLE | SS_LEFT , 40, 20, 50, 20, hwnd, NULL, NULL, NULL);
	hP_1 = CreateWindowEx(0, L"BUTTON", NULL, WS_CHILD | WS_VISIBLE | BS_BITMAP, 185, 60, 100, 60, hwnd, NULL, NULL, NULL);
	hP_2 = CreateWindowEx(0, L"BUTTON", NULL, WS_CHILD | WS_VISIBLE | BS_BITMAP, 45, 60, 100, 60, hwnd, NULL, NULL, NULL);
	SendMessage(hP_1, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hHp_1);
	hXYList = CreateWindowEx(WS_EX_CLIENTEDGE, L"LISTBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER  | WS_VSCROLL | SS_CENTER,40, 140, 249, 360, hwnd, NULL, NULL, NULL);

	if (sposob == 2)
	{
		DestroyWindow(Wozor_edit_1);
		SendMessage(hP_2, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hHp_2_2);
		linia = CreateWindowEx(0, L"STATIC", L"-------------------------------- +", WS_CHILD | WS_VISIBLE | SS_LEFT, 85, 19, 210, 14, hwnd, NULL, NULL, NULL);
		Wozor_edit_1 = CreateWindowEx(0, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_CENTER, 90, 5, 120, 20, hwnd, NULL, NULL, NULL);
		Wozor_edit_2 = CreateWindowEx(0, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_CENTER, 90, 31, 120, 20, hwnd, NULL, NULL, NULL);
		Wozor_edit_3 = CreateWindowEx(0, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_CENTER, 232, 18, 50, 20, hwnd, NULL, NULL, NULL);
	}
	else if (sposob == 1)
	{
		DestroyWindow(Wozor_edit_1);
		DestroyWindow(Wozor_edit_2);
		DestroyWindow(Wozor_edit_3);
		DestroyWindow(linia);
		SendMessage(hP_2, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hHp_2_1);
		Wozor_edit_1 = CreateWindowEx(0, L"EDIT", NULL, WS_CHILD | WS_VISIBLE, 90, 20, 200, 20, hwnd, NULL, NULL, NULL);
	};

	SendMessage(statyczny, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(Wozor_edit_1, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(Wozor_edit_2, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(Wozor_edit_3, WM_SETFONT, (WPARAM)hFont, TRUE);
	SendMessage(hXYList, WM_SETFONT, (WPARAM)hFont, TRUE);
};	

void AddMenu(HWND hWnd)
{
	HMENU hMenu = CreateMenu();
	HMENU hPlikiMenu = CreateMenu();
	HMENU hMotyw = CreateMenu();


	AppendMenu(hMotyw, MF_STRING, Nr_Menu_motyw_czerwony, L"Czerwony");
	AppendMenu(hMotyw, MF_STRING, Nr_Menu_motyw_rozowy, L"Różowy");
	AppendMenu(hMotyw, MF_STRING, Nr_Menu_motyw_niebieski, L"Niebieski");
	AppendMenu(hMotyw, MF_STRING, Nr_Menu_motyw_cyjan, L"Cyjan");
	AppendMenu(hMotyw, MF_STRING, Nr_Menu_motyw_zielony, L"Zielony");
	AppendMenu(hMotyw, MF_STRING, Nr_Menu_motyw_zolty, L"Żółty");

	AppendMenu(hPlikiMenu, MF_STRING, Nr_Menu_plik_wczytaj, L"Wczytaj");
	AppendMenu(hPlikiMenu, MF_STRING, Nr_Menu_plik_zapisz, L"Zapisz");
	AppendMenu(hPlikiMenu, MF_POPUP, (UINT_PTR)hMotyw, L"Motyw");
	AppendMenu(hPlikiMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hPlikiMenu, MF_STRING, Nr_Menu_plik_wyjscie, L"Wyjście");

	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hPlikiMenu, L"Plik");
	AppendMenu(hMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hMenu, MF_STRING, Nr_Menu_pomoc, L"Pomoc");

	SetMenu(hWnd, hMenu);
};

void zmiana_motywu(int Rr,int Gg,int Bb,HWND hwnd)
{
	R = Rr;
	G = Gg;
	B = Bb;
	DestroyWindow(hP_1);
	DestroyWindow(hP_2);
	DestroyWindow(statyczny);
	DestroyWindow(Wozor_edit_1);
	DestroyWindow(Wozor_edit_2);
	DestroyWindow(Wozor_edit_3);
	DestroyWindow(hXYList);
	DestroyWindow(text);
	DestroyWindow(linia);
	if ((R==255)&&(G==0)&&(B==0))
	{
		hHp_1 = (HBITMAP)LoadImage(NULL, L"Textures/hP_1_R.bmp", IMAGE_BITMAP, 100, 60, LR_LOADFROMFILE);
		hHp_2_1 = (HBITMAP)LoadImage(NULL, L"Textures/hP_2_1_R.bmp", IMAGE_BITMAP, 100, 60, LR_LOADFROMFILE);
		hHp_2_2 = (HBITMAP)LoadImage(NULL, L"Textures/hP_2_2_R.bmp", IMAGE_BITMAP, 100, 60, LR_LOADFROMFILE);
	}
	else if ((R == 255) && (G == 0) && (B == 255))
	{
		hHp_1 = (HBITMAP)LoadImage(NULL, L"Textures/hP_1_Ru.bmp", IMAGE_BITMAP, 100, 60, LR_LOADFROMFILE);
		hHp_2_1 = (HBITMAP)LoadImage(NULL, L"Textures/hP_2_1_Ru.bmp", IMAGE_BITMAP, 100, 60, LR_LOADFROMFILE);
		hHp_2_2 = (HBITMAP)LoadImage(NULL, L"Textures/hP_2_2_Ru.bmp", IMAGE_BITMAP, 100, 60, LR_LOADFROMFILE);
	}
	else if ((R == 0) && (G == 255) && (B == 255))
	{
		hHp_1 = (HBITMAP)LoadImage(NULL, L"Textures/hP_1_C.bmp", IMAGE_BITMAP, 100, 60, LR_LOADFROMFILE);
		hHp_2_1 = (HBITMAP)LoadImage(NULL, L"Textures/hP_2_1_C.bmp", IMAGE_BITMAP, 100, 60, LR_LOADFROMFILE);
		hHp_2_2 = (HBITMAP)LoadImage(NULL, L"Textures/hP_2_2_C.bmp", IMAGE_BITMAP, 100, 60, LR_LOADFROMFILE);
	}
	else if ((R == 255) && (G == 255) && (B == 0))
	{
		hHp_1 = (HBITMAP)LoadImage(NULL, L"Textures/hP_1_Z.bmp", IMAGE_BITMAP, 100, 60, LR_LOADFROMFILE);
		hHp_2_1 = (HBITMAP)LoadImage(NULL, L"Textures/hP_2_1_Z.bmp", IMAGE_BITMAP, 100, 60, LR_LOADFROMFILE);
		hHp_2_2 = (HBITMAP)LoadImage(NULL, L"Textures/hP_2_2_Z.bmp", IMAGE_BITMAP, 100, 60, LR_LOADFROMFILE);
	}
	else if ((R == 0) && (G == 255) && (B == 0))
	{
		hHp_1 = (HBITMAP)LoadImage(NULL, L"Textures/hP_1_G.bmp", IMAGE_BITMAP, 100, 60, LR_LOADFROMFILE);
		hHp_2_1 = (HBITMAP)LoadImage(NULL, L"Textures/hP_2_1_G.bmp", IMAGE_BITMAP, 100, 60, LR_LOADFROMFILE);
		hHp_2_2 = (HBITMAP)LoadImage(NULL, L"Textures/hP_2_2_G.bmp", IMAGE_BITMAP, 100, 60, LR_LOADFROMFILE);
	}
	else if ((R == 0) && (G == 0) && (B == 255))
	{
		hHp_1 = (HBITMAP)LoadImage(NULL, L"Textures/hP_1_B.bmp", IMAGE_BITMAP, 100, 60, LR_LOADFROMFILE);
		hHp_2_1 = (HBITMAP)LoadImage(NULL, L"Textures/hP_2_1_B.bmp", IMAGE_BITMAP, 100, 60, LR_LOADFROMFILE);
		hHp_2_2 = (HBITMAP)LoadImage(NULL, L"Textures/hP_2_2_B.bmp", IMAGE_BITMAP, 100, 60, LR_LOADFROMFILE);
	}

	fstream kolor;
	kolor.open("kolor.log", ios::out);

	kolor << R << endl;
	kolor << G << endl;
	kolor << B << endl;

	kolor.close();

	starterPack(hwnd);
};
