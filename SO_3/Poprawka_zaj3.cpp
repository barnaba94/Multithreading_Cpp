#include <iostream>
#include <windows.h>
#include <stdio.h>

#define MAX 10

DWORD tab1[MAX] = {0};
DWORD tab2[MAX] = {0};

using namespace std;

HANDLE pThreadA;
HANDLE pThreadB;

DWORD WINAPI watekA(LPVOID)
{
	while(1)
	{
		for(int i = 0; i< MAX ; i++)
		{
			if( tab1[i] < 9)
				tab1[i]++;
			else
				tab1[i] = 0;	
		}
	}
}
DWORD WINAPI watekB(LPVOID)
{
	while(1)
	{
		for(int i = 0; i< MAX ; i++)
		{
			if( tab2[i] < 9)
				tab2[i]++;
			else
				tab2[i] = 0;	
		}
	}
}

int main(int argc, char** argv)
{
	DWORD TAid , TBid;
	pThreadA = CreateThread( NULL, 0 , watekA , NULL , 0 , &TAid );
	pThreadB = CreateThread( NULL, 0 , watekB , NULL , 0 , &TBid );
	while(1)
	{
		Sleep(1000);
		for(int i = 0; i< MAX ; i++ )
			cout<<tab1[i];
		cout<<" ";
		for(int i = 0; i< MAX ; i++ )
			cout<<tab2[i];
		printf(" \n ");			
	}
	CloseHandle(pThreadA);		
	CloseHandle(pThreadB);
	return 0;
}
