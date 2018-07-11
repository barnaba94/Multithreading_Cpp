// SO_pipes.cpp : Defines the entry point for the console application.
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
	DWORD fConnected, dwWrite, bRet;
	char buf[100];

	pipe = CreateNamedPipeA("\\\\.\\pipe\\ThePipe",
		PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		BUFSIZE,
		BUFSIZE,
		0,
		NULL);

	fConnected = ConnectNamedPipe(pipe, NULL);

	while (1)
	{

		printf("Napisz cos:\n");
		gets_s(buf);

		bRet = WriteFile(pipe, buf, sizeof(buf), &dwWrite, NULL);

		bRet = ReadFile(pipe, buf, sizeof(buf), &dwWrite, NULL);
		cout << buf << endl;
	}
	system("pause");

	return 0;
}

