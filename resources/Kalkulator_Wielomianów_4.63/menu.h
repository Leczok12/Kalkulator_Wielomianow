#include <windows.h>
#include "wyliczanie.h"
class MENU
{
public:
	void zapisz()
	{
		MessageBox(NULL, L"zapis", L"B��d", MB_ICONWARNING | MB_OKCANCEL);
	};
	void wczytywanie(HWND hwnd)
	{
		Licz Llicz;
		OPENFILENAME otworz;
		
		char nazwa_pliku[100];

		ZeroMemory(&otworz, sizeof(OPENFILENAME));

		otworz.lStructSize = sizeof(OPENFILENAME);
		otworz.hwndOwner = hwnd;
		otworz.lpstrFile = (LPWSTR) nazwa_pliku;
		otworz.lpstrFile[0] = '\0';
		otworz.nMaxFile = 1000;
		otworz.lpstrFilter = L"Pliki Kalkulatora\0*.KWW";
		otworz.nFilterIndex = 1;

		GetOpenFileName(&otworz);

		//display_file(otworz.lpstrFile);

		MessageBox(NULL, L"wczytywanie", L"B��d", MB_ICONWARNING | MB_OKCANCEL);
	};
	void pomoc(HWND hwnd)
	{
		MessageBox(hwnd,L"W szare pole wprowad� malej�co wyrazy funkcji aby zamieni� z trdycyjnego wykresu na wykres funkcji homograficznej naci�nij 'W(x)=x/1' aby powrucic do tradycyjnej funkcji nasi�nij 'W(x)=x'. Przyk�adowy wz�r -1x^3-3x^2+4x+12. ",L"Pomoc",MB_OK|MB_ICONQUESTION);
	};
};