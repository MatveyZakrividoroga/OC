// Client.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include <iostream>
#include<Windows.h>
using namespace std;

int main()
{
    SECURITY_ATTRIBUTES sa; // атрибуты защиты
    SECURITY_DESCRIPTOR sd;
    HANDLE hNamedPipe;
    sa.nLength = sizeof(sa);
    sa.bInheritHandle = FALSE; // дескриптор канала ненаследуемый
    // инициализируем дескриптор защиты
    InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
    // устанавливаем атрибуты защиты, разрешая доступ всем пользователям
    SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);
    sa.lpSecurityDescriptor = &sd;
    hNamedPipe = CreateNamedPipe("\\\\.\\pipe\\demo_pipe", PIPE_ACCESS_DUPLEX, // читаем из канала и пишем в канал
        PIPE_TYPE_MESSAGE | PIPE_WAIT, // синхронная передача сообщений
        1, // максимальное количество экземпляров канала
        0, // размер выходного буфера по умолчанию
        0, // размер входного буфера по умолчанию
        INFINITE, // клиент ждет связь 500 мс
        &sa // доступ для всех пользователей
    );
    char c;
    cout << "Enter array size:" << "\n";
    int n;
    cin >> n;
    short* arr = new short[n];
    for (size_t i = 0; i < n; i++)
    {
        arr[i] = rand() % 100;
    }
    cout << '\n';
    for (size_t i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << "\n";
    if (hNamedPipe == INVALID_HANDLE_VALUE)
    {
        cerr << "Creation of the named pipe failed." << endl
            << "The last error code: " << GetLastError() << endl;
        cout << "Press any char to finish server: ";
        cin >> c;
        return 0;
    }
    ConnectNamedPipe(hNamedPipe, (LPOVERLAPPED)NULL);
 
    DWORD sz;
    WriteFile(hNamedPipe, &n, sizeof(n),&sz, (LPOVERLAPPED)NULL);
    for (size_t i = 0; i < n; i++)
    {
        DWORD size;
        WriteFile(hNamedPipe, &arr[i], sizeof(arr[i]), &size, NULL);
    }

    int m;
    ReadFile(hNamedPipe, &m, sizeof(m), &sz, NULL);
    short* h = new short[m];
    for (int i = 0; i < m; i++) {
        DWORD size;
        ReadFile(hNamedPipe, &h[i], sizeof(h[i]), &size, NULL);
    }
    for (int i = 0; i < m; i++) {
        cout << h[i] << " ";
    }
}