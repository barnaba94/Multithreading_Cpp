// SO2_terminate_process.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include "psapi.h"

void PrintProcesses(DWORD processID);
void KillProcess(DWORD processID);

int main()
{
	DWORD tablica_PIDow[1024], ilosc_bajtow, ilosc_procesow, kill;

	if (!EnumProcesses(tablica_PIDow, sizeof(tablica_PIDow), &ilosc_bajtow))
	{
		printf("blad!\n");
		return 1;
	}
	ilosc_procesow = ilosc_bajtow / sizeof(DWORD);

	for (int i = 0; i < ilosc_procesow; i++)
	{
		if (tablica_PIDow[i] != 0)
			PrintProcesses(tablica_PIDow[i]);
	}
	printf("\nilosc procesow: %u\n",ilosc_procesow);
	printf("podaj PID do zabicia: ");
	scanf("%d", &kill);
	KillProcess(kill);

	system("PAUSE");
    return 0;
}

void KillProcess(DWORD processID)
{
	HANDLE h = OpenProcess(PROCESS_ALL_ACCESS, 0, processID);
	if (!h)
	{
		printf("Process not found!\n");
		return;
	}
	TerminateProcess(h, 0);
}
void PrintProcesses(DWORD processID)
{
	LPWSTR lp[100] = { 0 };

	HANDLE h = OpenProcess(PROCESS_ALL_ACCESS, 0, processID);

	if (h)
	{
		HMODULE modh;
		DWORD bytes;

		if (EnumProcessModules(h, &modh, sizeof(modh), &bytes))
			GetModuleBaseName(h, FALSE,*lp, sizeof(lp)/sizeof(TCHAR));
	}
	printf("%s\t%u\n", lp,processID);
	CloseHandle(h);
}


