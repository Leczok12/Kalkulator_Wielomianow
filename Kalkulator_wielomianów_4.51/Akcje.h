#pragma once
#include "wyliczanie.h"
#include <windows.h>

Licz licz;

class Afffkcje
{
private:
	

public:
	int pixel;
	int spr = 0;

	void zmazanie(HWND hwnd)
	{
		HDC hdcOkno;
		HPEN czarny, Pudelko;
		HBRUSH czarny2, Pudelko2;

		POINT stary_punkt;
		czarny2 = CreateSolidBrush(0x000000);
		czarny = CreatePen(PS_SOLID, 1, 0x000000);
		hdcOkno = GetDC(hwnd);
		Pudelko = (HPEN)SelectObject(hdcOkno, czarny);
		Pudelko2 = (HBRUSH)SelectObject(hdcOkno, czarny2);


		Rectangle(hdcOkno, 350, 50, 752, 452);

		SelectObject(hdcOkno, Pudelko);
		DeleteObject(czarny);
		ReleaseDC(hwnd, hdcOkno);
	}
	void rysowanie_okna(HWND hwnd)
	{
		HDC hdcOkno;
		HPEN zielony, Pudelko;
		POINT stary_punkt;

		hdcOkno = GetDC(hwnd);
		zielony = CreatePen(PS_SOLID, 1, 0x00FF00);
		Pudelko = (HPEN)SelectObject(hdcOkno, zielony);

		MoveToEx(hdcOkno, 350, 50, &stary_punkt);
		LineTo(hdcOkno, 751, 50);

		MoveToEx(hdcOkno, 751, 50, &stary_punkt);
		LineTo(hdcOkno, 751, 451);

		MoveToEx(hdcOkno, 751, 451, &stary_punkt);
		LineTo(hdcOkno, 350, 451);

		MoveToEx(hdcOkno, 350, 451, &stary_punkt);
		LineTo(hdcOkno, 350, 50);

		MoveToEx(hdcOkno, 350, 251, &stary_punkt); //x
		LineTo(hdcOkno, 751, 251);

		MoveToEx(hdcOkno, 551, 50, &stary_punkt); //y
		LineTo(hdcOkno, 551, 451);

		SelectObject(hdcOkno, Pudelko);
		DeleteObject(zielony);
		ReleaseDC(hwnd, hdcOkno);
	};
	void wyrazy(HWND hwnd,HWND hSt)
	{
		
		wchar_t stopien[10];
		GetWindowText(hSt, stopien, 10);
		try
		{
			stopienint = std::stoi(stopien);
			spr = 1;
		}
		catch (const std::exception&)
		{
			MessageBeep(MB_ERR_INVALID_CHARS);
			spr = 0;
		}

		
		if (spr=1)
		{
			if ((stopienint >= 0) && (stopienint <= 15))
			{
				x = 70;
				for (int i = 0; i <= 15; i++)
				{
					DestroyWindow(hSwyrazy[i]);
					DestroyWindow(hWyrazy[i]);
				}
				hSwyrazy[0] = CreateWindowEx(0, L"STATIC", L"Podaj wyraz wolny : ", WS_CHILD | WS_VISIBLE | SS_LEFT, 5, 40, 130, 20, hwnd, NULL, NULL, NULL);
				hWyrazy[0] = CreateWindowEx(0, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 140, 38, 80, 20, hwnd, NULL, NULL, NULL);
				for (int i = 1; i <= stopienint; i++)
				{
					WCHAR text19[30] = { 'P','o','d','a','j',' ',i + '0',' ','w','y','r','a','z',' ',':' };
					WCHAR text1015[30] = { 'P','o','d','a','j',' ','1',i - 10 + '0',' ','w','y','r','a','z',' ',':' };
					if (i < 10)
					{
						hSwyrazy[i] = CreateWindowEx(0, L"STATIC", (LPCWSTR)text19, WS_CHILD | WS_VISIBLE | SS_LEFT, 5, x, 110, 20, hwnd, NULL, NULL, NULL);
						hWyrazy[i] = CreateWindowEx(0, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 120, x - 2, 80, 20, hwnd, NULL, NULL, NULL);
					}
					else
					{
						hSwyrazy[i] = CreateWindowEx(0, L"STATIC", (LPCWSTR)text1015, WS_CHILD | WS_VISIBLE | SS_LEFT, 5, x, 110, 20, hwnd, NULL, NULL, NULL);
						hWyrazy[i] = CreateWindowEx(0, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 120, x - 2, 80, 20, hwnd, NULL, NULL, NULL);
					};
					x = x + 30;
				}
			}
			else
			{
				MessageBox(NULL, L"Stopieñ nie mo¿e byæ wiêkszy od 15 i mniejszy od 0.", L"B³¹d", MB_ICONWARNING | MB_OKCANCEL);
			}

		}
		pixel = x;
	}
	void wpisywanie()
	{
		licz.st = stopienint;
		wchar_t wyraz[100];
		for (int i = 0; i <= stopienint; i++)
		{
			GetWindowText(hWyrazy[i], wyraz, 100);
			try
			{
				licz.wyrazy[i] = std::stof(wyraz);
			}
			catch (const std::exception&)
			{
				MessageBeep(MB_OK);
			}
			
		}


	}


};
