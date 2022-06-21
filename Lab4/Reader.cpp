
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<Windows.h>
#include <conio.h>
using namespace std;
int main()
{
	HANDLE exitR = OpenEvent(EVENT_ALL_ACCESS,FALSE, "reader");
	HANDLE mut = OpenMutex(SYNCHRONIZE, FALSE, "mutex");
	
	WaitForSingleObject(mut, INFINITE);
	HANDLE events[2];
	char p[2];
	for (size_t i = 0; i < 2; i++)
	{
		_itoa(i + 1, p, 10);
		events[i] = OpenEvent(SYNCHRONIZE, FALSE, p);
		if (events[i] == NULL) {
			GetLastError();
		}
	}


	DWORD ind;
	ind = WaitForMultipleObjects(2, events, FALSE, INFINITE);

	if (ind == 0) {
		cout << "A";
	}
	else {
		cout << "B";
	}
	
	_getch();
	ReleaseMutex(mut);
	SetEvent(exitR);
}


