// SO1.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <conio.h>
#include <time.h>
#include <windows.h>

int main()
{
	FILE* pf = fopen("text.txt", "r");
	if (!pf)
	{
		return 1;
	}
	char c;
	char line[200];
	int a = 1;
	while (a)
	{
		Sleep(1000);
		fgets(line, 200, pf);
		printf("%s", line);
		if (_kbhit() != 0)
			if ((c = _getch()) == 27)
				a = 0;
	}
	
    return 0;
}

