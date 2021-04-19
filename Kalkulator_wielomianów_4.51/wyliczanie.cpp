#include "wyliczanie.h"



void Licz::wypisywanieXYlista(HWND lista)
{
	wstringstream koniec(L"");
	wstringstream xr(L"x = ");
	wstringstream yr(L"  |  y = ");
	wstringstream xwynik(L"");
	wstringstream ywynik(L"");
	int d = -20;
	for (int i = 0; i <= 40; i++)
	{
		SendMessage(lista, LB_DELETESTRING, NULL, NULL);
	};
	for (int i = 0; i < 402; i)
	{

		xwynik.str(L"");
		ywynik.str(L"");
		koniec.str(L"");
		xr.str(L"");
		xwynik << d;
		if ((wyniki[i] >= -0.00000000001)&& (wyniki[i] <= 0.00000000001))
		{
			ywynik << "0";
		}
		else
		{
			ywynik << wyniki[i];
		};

		if (d < -9)
		{
			xr << "x =  ";
		}
		else if (d < 0)
		{
			xr << "x =    ";
		}
		else if (d > 9)
		{
			xr << "x =   ";
		}
		else if (d >= 0)
		{ 
			xr << "x =     ";
		};
		koniec << xr.str() + xwynik.str() + yr.str() + ywynik.str();
		SendMessage(lista, LB_ADDSTRING, i, (LPARAM)koniec.str().c_str());
		i = i + 10;
		d++;
	};
};

void Licz::wzor(HWND hWzor)
{
	wstringstream koniec(L"");
	wstringstream xx[7];
	for (int i = st; i >= 0; i--)
	{
		if ((wyrazy[i] > 0) && (i != 0))
		{
			wstringstream wyrazh(L"");
			wstringstream plus(L"+");
			wstringstream x(L"x");
			wstringstream potega(L"^");
			wstringstream potegaliczba(L"");
			wstringstream przerwa(L" ");
			wyrazh << wyrazy[i];
			potegaliczba << i;
			xx[i] << plus.str() + wyrazh.str() + x.str() + potega.str() + potegaliczba.str() + przerwa.str();
		}
		else if ((wyrazy[i] < 0) && (i != 0))
		{
			wstringstream wyrazh(L"");
			wstringstream x(L"x");
			wstringstream potega(L"^");
			wstringstream potegaliczba(L"");
			wstringstream przerwa(L" ");
			wyrazh << wyrazy[i];
			potegaliczba << i;
			xx[i] << wyrazh.str() + x.str() + potega.str() + potegaliczba.str() + przerwa.str();
		}
		else if ((wyrazy[i] < 0) && (i == 0))
		{
			wstringstream wyrazh(L"");
			wstringstream przerwa(L" ");
			wyrazh << wyrazy[i];
			xx[i] << wyrazh.str() + przerwa.str();
		}
		else if ((wyrazy[i] > 0) && (i == 0))
		{
			wstringstream plus(L"+");
			wstringstream wyrazh(L"");
			wstringstream przerwa(L" ");
			wyrazh << wyrazy[i];
			xx[i] << plus.str() + wyrazh.str() + przerwa.str();
		}
		else
		{
			xx[i] << (L"");
		};

	}
	for (int i = st; i < 7; i++)
	{
		xx[i] << (L"");
	}
	koniec << koniec.str() + xx[6].str() + xx[5].str() + xx[4].str() + xx[3].str() + xx[2].str() + xx[1].str() + xx[0].str();
	SetWindowTextW(hWzor, koniec.str().c_str());
};

void Licz::miejsca_zerowe(HWND hZero)
{
	wstringstream miejsca(L"W(x) = 0 gdy x ∈ ");
	wstringstream wyniks(L"");
	wstringstream wynikis(L"");
	if ((st == 0) && (wyrazy[0] == 0))
	{
		miejsca << miejsca.str() + L"R";
	}
	else
	{
		miejsca << miejsca.str() + L"{ ";
		double dd = -50.1;
		double wynik = 0;
		int stt = st;
		do
		{
			xx = xx + 0.1;
			if (stt!=0)
			{
				for (int i = 0; i <= st; i++)
				{
					if (i == 0)
					{
						wynik = wynik + wyrazy[0];
					}
					else
					{
						if (i > 1)
						{
							for (int j = 0; j < i; j++)
							{
								potega = potega * xx;
							}
						}
						else
						{
							potega = xx;
						}
						wynik = wynik + (wyrazy[i] * potega);
						potega = 1;
					};
				}
				if (wynik == 0)
				{
					wyniks << wynik;
					wynikis << wynikis.str() + wyniks.str() + L", ";
					stt--;
				};
				wynik = 0;
				wyniks.str(L"");
			}
			else
			{
				break;
			}
		} while (true);
		miejsca << miejsca.str() + wynikis.str() + L" }";
	};

	SetWindowTextW(hZero, miejsca.str().c_str());
}; //za dużo pamięci

void Licz::liczenie()//-x^3 -3x^2 +4x +12
{
	for (int i = 0; i <= 401; i++)
	{
		wyniki[i] = 0;
	};
	xx = -20.1;
	for (int x = 0; x <= 401; x++)
	{
		xx = xx + 0.1;
		for (int i = 0; i <= st; i++)
		{
			if (i == 0)
			{
				wyniki[x] = wyniki[x] + wyrazy[0];
			}
			else
			{
				if (i > 1)
				{
					for (int j = 0; j < i; j++)
					{
						potega = potega * xx;
					}
				}
				else
				{
					potega = xx;
				}
				wyniki[x] = wyniki[x] + (wyrazy[i] * potega);
				potega = 1;
			};
		}
	}
};

void Licz::wzor_rys(HWND hwnd)
{
	HDC hdcOkno;
	HPEN czerwony, Pudelko;
	HBRUSH czarny, Pudelko2;
	POINT stary_punkt;

	hdcOkno = GetDC(hwnd);
	czerwony = CreatePen(PS_SOLID, 1, 0xFFFF00);
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
	Rectangle(hdcOkno, 350, 452, 753,2000);

	SelectObject(hdcOkno, Pudelko2);
	DeleteObject(czarny);
	ReleaseDC(hwnd, hdcOkno);
};

void Licz::zmazanie(HWND hwnd)
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

void Licz::rysowanie_okna(HWND hwnd)
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

void Licz::pobieranie_wzor(HWND hwnd, HWND hSt)
{

	for (int i = 0; i <= sizeof(wyrazy); i++)
	{
		wyrazy[i] = 0;
	};

	double liczba = 0;
	int miejsca_zerowe = 0;
	int zero = 1;
	int akt_st = 0;
	wchar_t wzor[200];
	GetWindowText(hSt, wzor, 200);
	wstring convert(wzor);
	string wzor_s(convert.begin(), convert.end());
	st = 0;

	char znak[sizeof(wzor_s)];
	copy(begin(wzor_s), end(wzor_s), znak);
	if (wzor_s.size()!=0)
	{
		for (int i = wzor_s.size() - 1; i >= 0; i--)
		{

			if ((znak[i] == '0') || (znak[i] == '1') || (znak[i] == '2') || (znak[i] == '3') || (znak[i] == '4') || (znak[i] == '5') || (znak[i] == '6') || (znak[i] == '7') || (znak[i] == '8') || (znak[i] == '9') || (znak[i] == '.'))
			{
				if (znak[i] == '1')
				{
					liczba = liczba + (1 * zero);
					miejsca_zerowe++;
				}
				else if (znak[i] == '0')
				{
					miejsca_zerowe++;
				}
				else if (znak[i] == '2')
				{
					liczba = liczba + (2 * zero);
					miejsca_zerowe++;
				}
				else if (znak[i] == '3')
				{
					liczba = liczba + (3 * zero);
					miejsca_zerowe++;
				}
				else if (znak[i] == '4')
				{
					liczba = liczba + (4 * zero);
					miejsca_zerowe++;
				}
				else if (znak[i] == '5')
				{
					liczba = liczba + (5 * zero);
					miejsca_zerowe++;
				}
				else if (znak[i] == '6')
				{
					liczba = liczba + (6 * zero);
					miejsca_zerowe++;
				}
				else if (znak[i] == '7')
				{
					liczba = liczba + (7 * zero);
					miejsca_zerowe++;
				}
				else if (znak[i] == '8')
				{
					liczba = liczba + (8 * zero);
					miejsca_zerowe++;
				}
				else if (znak[i] == '9')
				{
					liczba = liczba + (9 * zero);
					miejsca_zerowe++;
				}
				else if (znak[i] == '.')
				{
					liczba = liczba / zero;
					miejsca_zerowe = 0;
				}
				zero = 1;
				for (int j = 0; j < miejsca_zerowe; j++)
				{
					zero = zero * 10;
				}
			}
			else if (znak[i] == '-')
			{
				zero = 1;
				liczba = liczba * -1;
				wyrazy[akt_st] = liczba;
				liczba = 0;
			}
			else if (znak[i] == '+')
			{
				miejsca_zerowe = 0;
				zero = 1;
				wyrazy[akt_st] = liczba;
				liczba = 0;
			}
			else if (znak[i] == '^')
			{

			}
			else if (znak[i] == ' ')
			{

			}
			else if (znak[i] == '*')
			{

			}
			else if ((znak[i] == 'x'))
			{
				if (znak[i + 1] != '^')
				{
					akt_st = 1;
					if (st <= akt_st)
					{
						st = akt_st;
					}
					miejsca_zerowe = 0;
					zero = 1;
					liczba = 0;
				}
				else
				{
					akt_st = liczba;
					if (st < akt_st)
					{
						st = akt_st;
					}
					miejsca_zerowe = 0;
					zero = 1;
					liczba = 0;
				};
			}
			else
			{
				MessageBox(hwnd, L"Błąd", L"Niepoprawny znak", MB_ICONWARNING);

				break;
			};
			if ((i == 0) && (znak[i] != '-'))
			{
				miejsca_zerowe = 0;
				zero = 1;
				wyrazy[akt_st] = liczba;
				liczba = 0;
			};

		};
	}
	else
	{
		MessageBox(NULL, L"brak danych", NULL, NULL);
	}
	
};

void Licz::wpisywanie()
{
	spr = 0;

	wchar_t wyraz[50];
	
	for (int d = 0; d <= st; d++)
	{
		GetWindowText(hWyrazy[d], wyraz, 50);
		try
		{
			spr = 1;
			wyrazy[d] = std::stof(wyraz);
		}
		catch (const std::exception&)
		{
			spr = 0;
			MessageBeep(MB_OK);
		}
	};
};