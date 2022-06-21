// Writer.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<Windows.h>
#include <conio.h>
using namespace std;
int main()
{
	HANDLE exitW = OpenEvent(EVENT_ALL_ACCESS, FALSE, "writer");
	HANDLE sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, "semaphore");
	
	
	if (sem == NULL) {
		GetLastError();
	}
	WaitForSingleObject(sem, INFINITE);
	HANDLE events[2];
	char p[2];
	for (size_t i = 0; i < 2; i++)
	{
		_itoa(i + 1, p, 10);
		events[i] = (HANDLE)CreateEvent(NULL, FALSE, FALSE, p);
		if (events[i] == NULL) {
			GetLastError();
		}
	}
	char c;
		cout << "Input message A or B\n";
		cin >> c;
		if (c == 'A') {
			SetEvent(events[0]);
		}
		else {
			SetEvent(events[1]);
		}	
	SetEvent(exitW);
	ReleaseSemaphore(sem,1,FALSE);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
