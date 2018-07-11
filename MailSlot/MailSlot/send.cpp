#include <stdio.h>
#include <windows.h>
#include <iostream>

HANDLE h1 = CreateFile( "\\\\.\\mailslot\\mailing", GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );

int main(int argc, char** argv)
{
	char buffor[400];
	char Message[400];
	DWORD dwWrite;
	printf("DO WYSLANIA: \n");
	gets( Message );
	for(int i=0; i < 100000; i++)
	{
		sprintf( buffor," %s ", Message);
		WriteFile( h1, buffor, strlen(Message)+1, &dwWrite, NULL );
	}
	return 0;
}
