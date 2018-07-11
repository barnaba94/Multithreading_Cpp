#include <windows.h>
#include <stdio.h>

#define MAX 100

int main(int argc, char** argv)
{
	HANDLE h1  = CreateMailslot( "\\\\.\\mailslot\\mailing", 0, MAILSLOT_WAIT_FOREVER, 0 );
	char Message[MAX];
	DWORD max, size, count, read, timeout, dwRead;

	while(1)
	{
		if( !GetMailslotInfo( h1, &max, &size, &count, &timeout ) )
		{
			printf(" SLOT ERROR!!! ");
		}
		else if( size == MAILSLOT_NO_MESSAGE )
		{
			printf(" NO MESSAGE!!! \n");
			Sleep(5000);
			continue;
		}
		printf(" RECEIVE MESSAGE:  ");
		ReadFile( h1, Message, size, &dwRead, NULL);
		printf( "%s %d\n", Message, count );
	}

    return 0;
}