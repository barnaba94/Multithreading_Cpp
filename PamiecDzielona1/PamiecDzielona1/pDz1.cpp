#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
	 
char nazwa[255] = "pam123456";
//char semafor[255] = "snz123456";

int main(int argc, char** argv)
{
	HANDLE hSem = NULL;
	HANDLE hPamiec;
	void* pBuf;
	char* tekst;
	int i = 0;
	hSem = CreateSemaphore(NULL, 0, 1, "snz123456" );
	if(hSem == NULL)
	{
		printf("Blad tworzenia semafora\n");
		return 1;
	}
	hPamiec = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 10000, nazwa);
	if(hPamiec == NULL)
	{
		printf("Blad przydzielenia pamieci!\n");
		return 1;
	}
	pBuf = MapViewOfFile( hPamiec , FILE_MAP_WRITE , 0 , 0 , 0);
	printf("Wprowadzaj tekst z klawiatury:\n");
	while( 1 )
	{
		(* (( int* )pBuf ) )++;
		gets( ( ( char* )pBuf + 4 ) );
		ReleaseSemaphore( hSem, 1, NULL );
	}
	UnmapViewOfFile( pBuf );
	CloseHandle( hPamiec );
	CloseHandle( hSem );	
	return 0;
}
