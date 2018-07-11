#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

char name[]="nazwa_map";
char nameofsemaphore[]="semafornazwany";

int main(int argc, char** argv)
{
	int count0 = 0;
	int count1 = 0;
	void* pBuffor;
	HANDLE hCreateMap, hMapping;
	HANDLE hSema;

	hSema = CreateSemaphore( NULL, 0, 1, nameofsemaphore);

	hCreateMap = OpenFileMapping( FILE_MAP_ALL_ACCESS, FALSE, name);
	if( !hCreateMap )
		return 1;
	pBuffor = MapViewOfFile( hCreateMap, FILE_MAP_READ, 0, 0, 0);
	while( 1 )
	{
		//Sleep(1000);
		WaitForSingleObject(hSema, INFINITE);
		count0 = *((int*)pBuffor);
		if(count0 != count1 )
		{
			printf("%d ", count0); 
			printf("%s \n", (char*)pBuffor+4);
			count1 = count0;
		}
	}
	UnmapViewOfFile( pBuffor );
	CloseHandle( hCreateMap );
	return 0;
}