#include <windows.h>
#include <stdio.h>
#include <sstream>
#pragma once

using namespace std;

class Licz
{
private:
	int x;
	double wyrazy[7];
	int st;
	double potega;
	double xx;
public:
	double wyniki[452];
	int spr = 0;
	
	Licz(float kWyrazy = 0,double kWyniki = 0,int kSt=0,double kPotega=1,double kXx=0)
	{
		for (int i = 0; i < 7; i++)
		{
			wyrazy[i] = kWyrazy;
		}
		for (int i = 0; i <= 451; i++)
		{
			wyniki[i] = kWyniki;
		}
		st = kSt;
		potega = kPotega;
		xx = kXx;
	}

	void wypisywanieXYlista(HWND lista);

	void wzor(HWND hWzor);

	void miejsca_zerowe(HWND hZero);

	void liczenie();

	void wzor_rys(HWND hwnd);

	void pobieranie_wzor(HWND hwnd, HWND hSt);
};