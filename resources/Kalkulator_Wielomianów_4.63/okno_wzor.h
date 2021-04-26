#include <Windows.h>

class okno_rys
{
public:
	void rys(HWND hwnd, int R, int G, int B)
	{
		HDC hdcOkno;
		HPEN pêdzel, Pudelko;
		POINT stary_punkt;

		hdcOkno = GetDC(hwnd);
		pêdzel = CreatePen(PS_SOLID, 1, RGB(R,G,B));
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
	};

private:

};