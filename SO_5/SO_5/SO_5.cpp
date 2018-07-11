// SO_5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>

volatile long bezsync = 0;
volatile long sync = 0;
//long licznik_sync = 0;
//long licznik_async = 0;

CRITICAL_SECTION cs1;
//CRITICAL_SECTION cs2;


DWORD WINAPI watek1(void* v)
{
	long licznik_op = 0;
	long licznik_OP1 = 0;
	while (1)
	{
		bezsync += 10;
		bezsync *=3;
		bezsync /= 3;
		bezsync -= 10;

		licznik_op++;
		//licznik_async++;
		//licznik_async--;
	}
	licznik_OP1++;
    //printf("%d %d", licznik_op, licznik_OP1);
	return 1;
}

DWORD WINAPI watek2(void* v)
{
	
	long licznik_op = 0;
	long licznik_OP2;
	
	
	/*while (!i)
	{
		Sleep(10);
		i = TryEnterCriticalSection(&cs1);
	}*/
	
	while (1)
	{
		EnterCriticalSection(&cs1);
		sync += 10;
		sync *= 3;
		sync /= 3;
		sync -= 10;

		licznik_op++;
		//licznik_sync++;
		//licznik_sync--;
		LeaveCriticalSection(&cs1);
	}

	licznik_OP2 = 0;
	
	return 2;
}

int main()
{
	InitializeCriticalSection(&cs1);

	HANDLE hw1a = CreateThread(0, 0, watek1, 0, 0, 0);
	//HANDLE hw1b = CreateThread(0, 0, watek1, 0, 0, 0);
	HANDLE hw2a = CreateThread(0, 0, watek2, 0, 0, 0);
	//HANDLE hw2b = CreateThread(0, 0, watek2, 0, 0, 0);

	for (int i = 0; i < 2; i++)
	{
		EnterCriticalSection(&cs1);
		printf("%d\t%d\n",bezsync,sync);
		LeaveCriticalSection(&cs1);
		Sleep(500);
	}

	DeleteCriticalSection(&cs1);
    return 0;
}

