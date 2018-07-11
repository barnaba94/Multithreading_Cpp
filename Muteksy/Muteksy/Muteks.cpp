#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_TAB 20
#define WAIT 8000

HANDLE hMutex;
HANDLE hMan, hWoman;

volatile char Prysznic[ MAX_TAB ] = {0};

DWORD WINAPI man(void*)
{
	int i, j;
	while(1)
	{
		WaitForSingleObject( hMutex, INFINITE );
		for( i = 0; i < MAX_TAB ; i++)
			Prysznic[i] = 'M';
		ReleaseMutex( hMutex );
	}
}

DWORD WINAPI woman(void*)
{
	int i, j;
	while(1)
	{
		WaitForSingleObject( hMutex, INFINITE );
		for( i = 0; i < MAX_TAB ; i++)
			Prysznic[i] = 'K';
		ReleaseMutex( hMutex );
	}
}

int main(int argc, char** argv)
{
	int k;
	hMutex = CreateMutex( NULL, FALSE, NULL );
	hMan = CreateThread(NULL, 0, man, NULL, 0, NULL);
	hWoman = CreateThread(NULL, 0, woman, NULL, 0, NULL);

	while( 1 )
	{
		WaitForSingleObject( hMutex, INFINITE );
		for( k = 0; k < MAX_TAB ; k++)
		{
			printf("%c", Prysznic[k] );
			if( ( k+1) % 20 == 0)
				printf("\n\n");
		}
		ReleaseMutex( hMutex );
		Sleep( 1000 );
		printf("\n\n");
	}
	
	CloseHandle( hMutex );
	CloseHandle( hMan );
	CloseHandle( hWoman );
	return 0;
}