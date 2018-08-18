// Fill out your copyright notice in the Description page of Project Settings.

#include "SwordMousePostion.h"
#include <string>
#include <windows.h>

using namespace std;

bool USwordMousePostion::SwordMousePosition()
{
	POINT p;
	int x = 0;
	 
	if (GetCursorPos(&p))
	{
		//cursor position now in p.x and p.y

		x = p.x;
		
	}
	int cx = GetSystemMetrics(SM_CXSCREEN);
	cx = cx / 2;
	if (cx < x)
	{
		return false;
	}
	else
	{
		return true;
	}

	
	
}


