
class Super
{
public:
	double wyniki[452];
	int bledy[452];

	void liczenie(double w1, double w2, int i, double dodatkowa = 0 )
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
			wyniki[i] = w1 / w2 + dodatkowa;
			bledy[i] = 1;
		}
		else
		{
			wyniki[i] = w1 / w2 + dodatkowa;
		};
		
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
};
