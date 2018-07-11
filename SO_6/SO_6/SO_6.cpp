// SO_6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <windows.h>
#include <conio.h>

int main()
{
	HANDLE sem = OpenSemaphore(SEMAPHORE_MODIFY_STATE, FALSE, L"sem1");
	while (_getch() != 1)
		;
	ReleaseSemaphore(sem, 1, NULL);
	CloseHandle(sem);
	return 0;
}
int main()
{
	HANDLE sem[] = { CreateSemaphore(NULL, 0,1, L"sem1"),CreateSemaphore(NULL, 0,1, L"sem2") };
	WaitForMultipleObjects(2, sem, TRUE, INFINITE);

	printf("semaphores released\n");
	CloseHandle(sem[0]);
	CloseHandle(sem[1]);

    return 0;
}

