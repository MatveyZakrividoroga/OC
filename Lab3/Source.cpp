#include<iostream>;
#include<Windows.h>;
using namespace std;
HANDLE MultEvent,workEvent;
CRITICAL_SECTION cs;
struct arr{
	int n;
	double *ar;
};
DWORD WINAPI work(arr *a) {
	EnterCriticalSection(&cs);
	DWORD t;
	cout << "Input sleep time\n";
	cin >> t;
	for (int i = 0; i < a->n; i++) {
		for (int j = i + 1; j < a->n; j++) {
			if (a->ar[i] == a->ar[j]) {
				double temp;
				temp = a->ar[i + 1];
				a->ar[i + 1] = a->ar[j];
				a->ar[j] = temp;
			}
		}
		Sleep(t);
	}
	for (int i = 0; i < a->n; i++) {
		cout << a->ar[i] << " ";
	}
	cout << endl;
	LeaveCriticalSection(&cs);
	return 0;
}
double mult = 1;
DWORD WINAPI MultElement(arr *a) {
	EnterCriticalSection(&cs);
	int i = 0;	
	while (i!=a->n) {
		mult *= a->ar[i];
		i++;
		Sleep(200);
	}
	LeaveCriticalSection(&cs);
	DeleteCriticalSection(&cs);
	SetEvent(MultEvent);
	return 0;
}
int main() {
	arr a;
	cout << "Enter array size:";
	cin >> a.n;
	a.ar = new double[a.n];
	for (int i = 0; i < a.n; i++) {
		cin >> a.ar[i];
	}
	cout << "Array size: " << a.n << endl;
	cout << "Array: ";
	for (int i = 0; i < a.n; i++) {
		cout << a.ar[i];
	}
	cout << endl;
	HANDLE hWork, hMultElement;
	DWORD idWork, idMultElement;
	InitializeCriticalSection(&cs);
	MultEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (MultEvent == NULL) {
		GetLastError();
	}
	hWork = (HANDLE)CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)work, &a, 0, &idWork);
	if (hWork == NULL) {
		GetLastError();
	}

	hMultElement = (HANDLE)CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MultElement, &a, 0, &idMultElement);
	if (hMultElement == NULL) {
		GetLastError();
	}
	WaitForSingleObject(hWork, INFINITE);
	CloseHandle(hWork);
	
	WaitForSingleObject(MultEvent, INFINITE);
	cout << "MultElements:" << endl;
	cout << mult;
	WaitForSingleObject(hMultElement, INFINITE);
	CloseHandle(hMultElement);
}
	


