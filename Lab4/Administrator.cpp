// OC(4).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<Windows.h>
#include <conio.h>
using namespace std;
int main()
{
    HANDLE eX[2];
    eX[0] = CreateEvent(NULL, FALSE, FALSE, "writer");
    eX[1] = CreateEvent(NULL, FALSE, FALSE, "reader");

    int n, m;
    cout << "Input number of Writer processes\n";
    cin >> n;
    cout << "Input number of Reader processes\n";
    cin >> m;
    HANDLE sem = CreateSemaphore(NULL, 3, 3, "semaphore");
    HANDLE* proc = new HANDLE[n + m];
    HANDLE events[2];
    HANDLE mut;
    DWORD* id = new DWORD[n + m];
    STARTUPINFO* st = new STARTUPINFO[n + m];
    PROCESS_INFORMATION* pi = new PROCESS_INFORMATION[n + m];
    char p[2];
   
    mut = CreateMutex(NULL, FALSE, "mutex");
    if (mut == NULL) {
        GetLastError();
    }
    for (int i = 0; i < n; i++) {
        ZeroMemory(&st[i], sizeof(STARTUPINFO));
        st[i].cb = sizeof(STARTUPINFO);
        CreateProcess(NULL, (LPSTR)("Writer.exe"), NULL, NULL, FALSE,
            CREATE_NEW_CONSOLE, NULL, NULL, &st[i], &pi[i]);
    }
    for (size_t i = n; i < n + m; i++)
    {
        ZeroMemory(&st[i], sizeof(STARTUPINFO));
        st[i].cb = sizeof(STARTUPINFO);
        CreateProcess(NULL, (LPSTR)("Reader.exe"), NULL, NULL, FALSE,
            CREATE_NEW_CONSOLE, NULL, NULL, &st[i], &pi[i]);
    }
    Sleep(100);
    
    DWORD ind;
    Sleep(100);
    for (int i = 0; i < n + m; i++) {
        ind = WaitForMultipleObjects(2, eX, FALSE, INFINITE);
        if (ind == 0) {
            cout << "Writer ended his work\n";
        }
        else {
            cout << "Reader ended his work\n";
        }
    }
    _getch();
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
