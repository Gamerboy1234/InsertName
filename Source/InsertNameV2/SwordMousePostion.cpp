// Fill out your copyright notice in the Description page of Project Settings.

#include <string>
#include <windows.h>
#include "SwordMousePostion.h"
using namespace std;

FString USwordMousePostion::SwordMousePosition()
{
	POINT p;
	int x = 0;
	int y = 0;
	if (GetCursorPos(&p))
	{
		//cursor position now in p.x and p.y

		x = p.x;
		y = p.y;
	}

	string bob = "";
	bob = to_string(x);

	FString jim(bob.c_str());
	return jim;
}



