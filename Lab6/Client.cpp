// Client.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include <iostream>
#include<Windows.h>
using namespace std;

int main()
{
    HANDLE hNamedPipe;
    hNamedPipe = CreateFile(
        "\\\\.\\pipe\\demo_pipe", // имя канала
        GENERIC_READ | GENERIC_WRITE, // читаем и записываем в канал
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        (LPSECURITY_ATTRIBUTES)NULL, // защита по умолчанию
        OPEN_EXISTING, // открываем существующий канал
        0, // атрибуты по умолчанию
        (HANDLE)NULL // дополнительных атрибутов нет
    );
    
    cout << "Enter N,M\n";
    int M, N;
    cin >> N >> M;
    char h = 'h';
    DWORD sz;
    int n;
    ReadFile(hNamedPipe, &n, sizeof(n), &sz, (LPOVERLAPPED)NULL);
    short* ar = new short[n];
    for (int i = 0; i < n; i++) {
        DWORD s;
        ReadFile(hNamedPipe, &ar[i], sizeof(ar[i]), &s, NULL);
    }
    for (int i = 0; i < n; i++) {
        cout << ar[i] << " ";
    }
    int ind=0;
    for (int i = 0; i < n; i++) {
        if (N <= ar[i] && ar[i] <= M) {
            ind++;
        }
    }
    short* ar1 = new short[ind];
    ind = 0;
    for (int i = 0; i < n; i++) {
        if (N <= ar[i] && ar[i] <= M) {
            ar1[ind] = ar[i];
            ind++;
        }

    }
    WriteFile(hNamedPipe, &ind, sizeof(ind), &sz, NULL);
    for (size_t i = 0; i < ind; i++)
    {
        DWORD r;
        WriteFile(hNamedPipe, &ar1[i], sizeof(ar1[i]), &r, NULL);

    }
    cout << endl;
    for (size_t i = 0; i < ind; i++) {
        cout << ar1[i] << " ";
    }
    int a;
    cin >> a;
    //WriteFile(hNamedPipe, &h, sizeof(h), &sz, (LPOVERLAPPED)NULL);
    //ReadFile(hNamedPipe, &r, sizeof(r), &sz, (LPOVERLAPPED)NULL);
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
