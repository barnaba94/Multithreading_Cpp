// SO_4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>
#pragma comment(lib,"winmm")

int z1 = 0;
volatile long z2 = 0;
long z3 = 0;
DWORD timeZ1;
DWORD timeZ2;
DWORD timeZ3;

DWORD WINAPI watek1(void* v)
{
	while(1)
	{
		DWORD z1t1 = timeGetTime();
		z1 += 3;
		z1--;
		z1--;
		z1--;
		DWORD z1t2 = timeGetTime();
		timeZ1 = z1t2 - z1t2;
		z2 += 3;
		z2--;
		z2--;
		z2--;
		DWORD z3t1 = timeGetTime();
		InterlockedExchangeAdd(&z3, 3);
		InterlockedDecrement(&z3);
		InterlockedDecrement(&z3);
		InterlockedDecrement(&z3);
		DWORD z3t2 = timeGetTime();
		timeZ3 = z3t2 - z3t2;
	}
}

DWORD WINAPI watek2(void* v)
{
	while (1)
	{
		z1 += 3;
		z1--;
		z1--;
		z1--;

		z2 += 3;
		z2--;
		z2--;
		z2--;

		InterlockedExchangeAdd(&z3, 3);
		InterlockedDecrement(&z3);
		InterlockedDecrement(&z3);
		InterlockedDecrement(&z3);
	}
}
DWORD WINAPI watek3(void* v)
{
	while (1)
	{
		z1 += 3;
		z1--;
		z1--;
		z1--;

		z2 += 3;
		z2--;
		z2--;
		z2--;

		InterlockedExchangeAdd(&z3, 3);
		InterlockedDecrement(&z3);
		InterlockedDecrement(&z3);
		InterlockedDecrement(&z3);
	}
}

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE process = GetCurrentProcess();
	SetPriorityClass(process, ABOVE_NORMAL_PRIORITY_CLASS);
	HANDLE hw1, hw2, hw3;

	hw1 = CreateThread(0, 0, watek1, 0, 0, 0);
	hw2 = CreateThread(0, 0, watek2, 0, 0, 0);
	hw3 = CreateThread(0, 0, watek3, 0, 0, 0);

	HANDLE watek_glowny = GetCurrentThread();
	SetThreadPriority(watek_glowny, THREAD_PRIORITY_NORMAL);

	for (int i = 0; i < 10; i++)
	{
		Sleep(1000);
		printf("z1 = %d, %d\tz2 = %d\tz3 = %d, %d\n", z1,timeZ1, z2, z3, timeZ3);
	}
	
	CloseHandle(hw1);
	CloseHandle(hw2);
	CloseHandle(hw3);
    return 0;
}

