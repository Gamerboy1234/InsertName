// Fill out your copyright notice in the Description page of Project Settings.

#include "MousePostionY.h"
#include <string>
#include <windows.h>

using namespace std;

int UMousePostionY::MouseY()
{
	POINT p;
	int y = 0;

	if (GetCursorPos(&p))
	{
		//cursor position now in p.x and p.y

		y = p.y;

	}
	int sy = GetSystemMetrics(SM_CYSCREEN);
	sy = sy / 2;
	if (sy < y)
	{
		
	}
	return y;
}



