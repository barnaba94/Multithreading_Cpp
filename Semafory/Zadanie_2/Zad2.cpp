#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

HANDLE h1, h2, h3;

int main( int argc, char** argv )
{
	h1 = CreateSemaphore( NULL, 0, 1, "sem1" );
	while( _getch() != '1');
	ReleaseSemaphore( h1, 1, NULL );
	CloseHandle( h1 );
	return 0;
}