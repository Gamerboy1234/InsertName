// Fill out your copyright notice in the Description page of Project Settings.

#include "MouseX.h"
#include <string>
#include <windows.h>
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"



using namespace std;

int UMouseX::MouseX()
{
	POINT p;
	int x = 0;

	if (GetCursorPos(&p))
	{
		//cursor position now in p.x and p.y

		x = p.x;

	}
	
	/*
	int cx = GetSystemMetrics(SM_CYSCREEN);

	cx = cx / 2;

	return cx;
	*/

	return p.x;
}
