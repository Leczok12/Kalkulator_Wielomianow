#include "okno_wzor.h"

void okno_rys::rys(HWND hwnd, int R, int G, int B)
{
	HDC hdcOkno;
	HPEN pêdzel, Pudelko;
	POINT stary_punkt;

	hdcOkno = GetDC(hwnd);
	pêdzel = CreatePen(PS_SOLID, 1, RGB(R, G, B));
	Pudelko = (HPEN)SelectObject(hdcOkno, pêdzel);

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
	for (int i = 361; i < 751; i = i + 10)
	{
		MoveToEx(hdcOkno, i, 249, &stary_punkt);
		LineTo(hdcOkno, i, 254);
	};
	MoveToEx(hdcOkno, 551, 50, &stary_punkt); //y
	LineTo(hdcOkno, 551, 451);
	for (int i = 61; i < 451; i = i + 10)
	{
		MoveToEx(hdcOkno, 549, i, &stary_punkt);
		LineTo(hdcOkno, 554, i);
	};
	SelectObject(hdcOkno, Pudelko);
	DeleteObject(pêdzel);
	ReleaseDC(hwnd, hdcOkno);
};

void okno_rys::zmazanie(HWND hwnd)
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
};

void okno_rys::wzor(double wyniki[452], HWND hwnd, int R, int G, int B)
{
	HDC hdcOkno;
	HPEN czerwony, Pudelko;
	HBRUSH czarny, Pudelko2;
	POINT stary_punkt;

	hdcOkno = GetDC(hwnd);
	czerwony = CreatePen(PS_SOLID, 1, RGB(R, G, B));
	czarny = CreateSolidBrush(0x000000);
	Pudelko = (HPEN)SelectObject(hdcOkno, czerwony);

	for (int i = 0; i <= 400; i++)
	{

		MoveToEx(hdcOkno, i + 351, 251 - int(wyniki[i] * 10), &stary_punkt);
		LineTo(hdcOkno, i + 352, 252 - int(wyniki[i + 1] * 10));

	};
	SelectObject(hdcOkno, Pudelko);
	DeleteObject(czerwony);

	Pudelko2 = (HBRUSH)SelectObject(hdcOkno, czarny);
	Rectangle(hdcOkno, 350, 0, 753, 50);
	Rectangle(hdcOkno, 350, 452, 753, 2000);

	SelectObject(hdcOkno, Pudelko2);
	DeleteObject(czarny);
	ReleaseDC(hwnd, hdcOkno);
};