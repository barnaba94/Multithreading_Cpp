#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

char name[]="nazwa_map";
char nameofsemaphore[]="semafornazwany";


int main(int argc, char** argv)
{
	void* pBuffor;
	HANDLE hCreateMap, hMapping, hSema;

	hSema = CreateSemaphore( NULL, 0, 1, nameofsemaphore);

	hCreateMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL , PAGE_READWRITE, 0, 5000, name);
	if( !hCreateMap )
		return 1;
	pBuffor = MapViewOfFile(hCreateMap, FILE_MAP_WRITE, 0, 0, 0);
	printf("Powiedz cos: ");
	while( 1 )
	{
		( *((int*)pBuffor))++;
		gets( (char*)pBuffor+4);
		ReleaseSemaphore( hSema, 1, NULL );
	}
	UnmapViewOfFile( pBuffor );
	CloseHandle( hCreateMap );
	return 0;
}