// SO_pipesClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>
#include <iostream>
using namespace std;
int BUFSIZE = 1000;

int main()
{
	HANDLE pipe;
	DWORD fConnected, dwRead;
	BOOL bRet;
	char buf[100];

	pipe = CreateFileA("\\\\.\\pipe\\ThePipe", GENERIC_ALL, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	while (1)
	{
		bRet = ReadFile(pipe, buf, sizeof(buf), &dwRead, NULL);

		printf("%s\n", buf);
		cout <<endl << "odpowiedz:" << endl;

		gets_s(buf);

		bRet = WriteFile(pipe, buf, sizeof(buf), &dwRead, NULL);
	}
	system("pause");

	
    return 0;
}

