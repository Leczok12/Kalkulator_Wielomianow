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
		MessageBox(NULL, L"odczyt", L"B��d", MB_ICONWARNING | MB_OKCANCEL);
	};
	void pomoc(HWND hwnd)
	{
		MessageBox(hwnd,L"W szare pole wprowad� malej�co wyrazy, aby zmieni� z tradycyjnego wykresu na wykres funkcji homograficznej naci�nij \"W(x)=x/1\", aby powr�ci� do tradycyjnej funkcji naci�nij \"W(x)=x\". Przyk�adowy wz�r: -1x^3-3x^2+4x+12.",L"Pomoc",MB_OK|MB_ICONQUESTION);
	};
};