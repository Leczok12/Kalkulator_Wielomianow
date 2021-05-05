#include <windows.h>
#include "wyliczanie.h"
class MENU
{
public:
	void zapisz()
	{
		MessageBox(NULL, L"zapis", L"B³¹d", MB_ICONWARNING | MB_OKCANCEL);
	};
	void wczytywanie(HWND hwnd)
	{
		MessageBox(NULL, L"odczyt", L"B³¹d", MB_ICONWARNING | MB_OKCANCEL);
	};
	void pomoc(HWND hwnd)
	{
		MessageBox(hwnd,L"W szare pole wprowadŸ malej¹co wyrazy, aby zmieniæ z tradycyjnego wykresu na wykres funkcji homograficznej naciœnij \"W(x)=x/1\", aby powróciæ do tradycyjnej funkcji naciœnij \"W(x)=x\". Przyk³adowy wzór: -1x^3-3x^2+4x+12.",L"Pomoc",MB_OK|MB_ICONQUESTION);
	};
};