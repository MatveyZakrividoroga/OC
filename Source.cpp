#include <windows.h>
#include <iostream>
#include <process.h>
using namespace std;
struct arr {
	int k;
	int n;
	unsigned long* a ;
};
DWORD WINAPI sum(arr* ar) {
	unsigned long temp;
	unsigned long t=0;
	int y = 0;
	for (int i = 0; i < ar->n; i++) {
		t = 0;
		temp = ar->a[i];
		while (temp != 0) {
			t += temp % 10;
			//ar->a[i]=ar->a[i] / 10;
			temp = temp / 10;
		}
		if (t == ar->k) {
			cout << ar->a[i] <<" ";
			y++;
		}
		Sleep(20);
	}

	if (y == 0) { cout << "Elements not found"; }
	return 0;
}
int main() {
	arr massiv;
	cout << "Input k:" << endl;
	cin >> massiv.k;
	cout << "Input Array size n:" << endl;
	cin >> massiv.n;
	cout << "Input Array elements:" << endl;
	massiv.a = new unsigned long[massiv.n];
	for (int i = 0; i < massiv.n; i++) {
		cin >> massiv.a[i];
	}
	HANDLE	worker;
	DWORD	IDworker;
	char c;
	worker = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)sum, &massiv, 0, &IDworker);
	if (worker == NULL) {
		return GetLastError();
	}
	SuspendThread(worker);
		cout << "Input " << endl;
		cout << "\t'r' to resume thread" << endl;
		cout << "\t't' to terminate thread" << endl;
		cin >> c;
		
		if (c == 'r') {
			ResumeThread(worker);
			WaitForSingleObject(worker, 100);
		}
		if (c == 't') {
			TerminateThread(worker, 0);
		}
		
		CloseHandle(worker);



		cout << endl;
		cout << "///////////////////////////////////////////////////////////////////////////////////";
		cout << endl;
		unsigned thrID;
		worker = (HANDLE)_beginthreadex(NULL, 0, (_beginthreadex_proc_type)sum, &massiv, 0, &thrID);
		if (worker == NULL) {
			return GetLastError();
		}
		WaitForSingleObject(worker, INFINITE);
		TerminateThread(worker, 0);
		CloseHandle(worker);

}