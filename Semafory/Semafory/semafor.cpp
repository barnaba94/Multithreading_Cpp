#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include<conio.h>

long bezsync = 0;
long sync = 0;

long loperacji1 = 0;
long loperacji2 = 0; 
long loperacji3 = 0; 

HANDLE hMutex;
HANDLE hSemafor;

DWORD WINAPI watek1(void*)
{
	while(1)
	{
		//Sleep(500);
		bezsync+=10;
		//Sleep(500);
		bezsync*=3;
	    //Sleep(500);
		bezsync/=3;
		//Sleep(500);
		bezsync-=10;
		//Sleep(500);
		loperacji1++;
		//Sleep(500);
	}
}

DWORD WINAPI mutex(void*)
{
	
	while(1)
	{
		WaitForSingleObject( hMutex, INFINITE );
		//Sleep(500);
		sync+=10;
		//Sleep(500);
		sync*=3;
		//Sleep(500);
		sync/=3;
		//Sleep(500);
		sync-=10;
		//Sleep(500);
		loperacji2++;
		//Sleep(500);
		ReleaseMutex( hMutex);
	}
}
//
DWORD WINAPI semafor(void*)
{
	while(1)
	{
		WaitForSingleObject( hSemafor, INFINITE );
		sync+=10;
		sync*=3;
		sync/=3;
		sync-=10;
		loperacji2++;
		ReleaseSemaphore( hSemafor, 1, NULL);
	}
}
//==============================================================================
int main(int argc, char** argv)
{
	//hMutex = CreateMutex(NULL, FALSE, NULL);
	hSemafor = CreateSemaphore(NULL, 1, 1, NULL);

	HANDLE h1, h2, h3;

	h1 = CreateThread(NULL, 0, watek1, NULL, 0, NULL);
	//h2 = CreateThread(NULL, 0, mutex, NULL, 0, NULL);
	h3 = CreateThread(NULL, 0, semafor, NULL, 0, NULL);
	

	while(1)
	{
		Sleep(500);
		printf("licznik_watek1: %d  licznik_semaphore: %d sync: %d  bezsync: %d \n", loperacji1, loperacji2, sync, bezsync);
	}

	CloseHandle( h1 );
	//CloseHandle( h2 );
	CloseHandle( hSemafor );
	
	return 0;
}