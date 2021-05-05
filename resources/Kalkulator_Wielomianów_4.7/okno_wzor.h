#include <Windows.h>

class okno_rys
{
public:
	void rys(HWND hwnd, int R, int G, int B);
	
	void zmazanie(HWND hwnd);

	void wzor(double wyniki[452], HWND hwnd, int R, int G, int B);
};