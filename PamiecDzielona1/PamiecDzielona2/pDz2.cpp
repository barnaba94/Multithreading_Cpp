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
		int n1 = 0, n2 = 0;
		int i = 0;
		hSem = CreateSemaphore(NULL, 0, 1, "snz123456");
		if(hSem == NULL)
		{
			printf("Blad tworzenia semafora\n");
			return 1;
		}
		hPamiec = OpenFileMapping( FILE_MAP_ALL_ACCESS , 0 , nazwa);
		if( hPamiec == NULL )
		{
			printf("Blad otwarcia pamieci!\nWlacz proces, ktory przydziela pamiec dzielona\n");
			return 1;
		}
		pBuf = MapViewOfFile(hPamiec, FILE_MAP_READ , 0, 0, 0 );
		while(1)
		{
			WaitForSingleObject(hSem, INFINITE);
			n1 =*( int* )pBuf;
			if(n1 != n2)
			{
				printf("%d\t", n1);
				printf("%s\n",( ( char* )pBuf+4) );
				n2 = n1;
			}
	 
		}
		UnmapViewOfFile( pBuf );
		CloseHandle( hPamiec );
		CloseHandle( hSem );
		return 0;
}