#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


int main( int argc, char** argv )
{
	HANDLE h1[] = { CreateSemaphore( NULL, 0, 1, "sem1" ), CreateSemaphore( NULL, 0, 1, "sem2" )};
	while( _getch() != '1' );
	ReleaseSemaphore( h1[0], 1, NULL );
	while( _getch() != '2' );
	ReleaseSemaphore( h1[1], 1, NULL );
	WaitForMultipleObjects( 2, h1, TRUE,  INFINITE);

	printf("Semaphores released!!!");
	CloseHandle( h1[0] );
	CloseHandle( h1[1] );

	return 0;
}