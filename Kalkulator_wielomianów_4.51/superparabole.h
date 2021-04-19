
class Super
{
public:
	double wyniki[452];
	int bledy[452];

	void liczenie(double w1, double w2, int i)
	{
		if (i==0)
		{
			for (int i = 0; i < 450; i++)
			{
				bledy[i] = 0;
			};
		}
		if ((w2 >= -0.00000000001) && (w2 <= 0.00000000001))
		{
			wyniki[i] = w1 / w2;
			bledy[i] = 1;
		}
		else
		{
			wyniki[i] = w1 / w2;
		};
		
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
	
	void wypisywanieXYlista(HWND lista)
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
			if ((wyniki[i] >= -0.00000000001) && (wyniki[i] <= 0.00000000001))
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

			if ((isnan(wyniki[i]))||(isinf(wyniki[i]))||(bledy[i] == 1))
			{
				koniec << xr.str() + xwynik.str() + yr.str() + L"dzielenie przez 0";
			}
			else
			{
				koniec << xr.str() + xwynik.str() + yr.str() + ywynik.str();
			};
			SendMessage(lista, LB_ADDSTRING, i, (LPARAM)koniec.str().c_str());
			i = i + 10;
			d++;
		};
	};

	void wzor_rys(HWND hwnd)
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
		Rectangle(hdcOkno, 350, 452, 753, 2000);

		SelectObject(hdcOkno, Pudelko2);
		DeleteObject(czarny);
		ReleaseDC(hwnd, hdcOkno);
	};
private:

};
