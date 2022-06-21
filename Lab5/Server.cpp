#include <iostream>
#include<conio.h>
#include<Windows.h>
using namespace std;

int main()
{
    
    HANDLE write, read;
    HANDLE end = CreateEvent(NULL, FALSE, FALSE, "end");
    if (end == NULL) {
        GetLastError();
    }
    int n;
    cout << "Enter array size \n";

    cin >> n;
    short* arr = new short[n];

    for (size_t i = 0; i < n; i++)
    {
        arr[i] = rand() % 100;
    }
    cout << '\n';
    for (size_t i = 0; i < n; i++)
    {
        cout << arr[i]<<" ";
    }
    cout << "\n";
    HANDLE event = CreateEvent(NULL, FALSE, FALSE, "1");
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL; 
    sa.bInheritHandle = TRUE;
    CreatePipe(&read, &write, &sa, 0);
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    char a[80];
    wsprintf(a, "Part.exe %d %d %d", int(write), int(read), n);

    if (!CreateProcess(NULL, a, NULL, NULL, TRUE,
        CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
        GetLastError();
    }
  
    for (size_t i = 0; i < n; i++)
    {
        DWORD size;
        WriteFile(write, &arr[i], sizeof(arr[i]), &size, NULL);
    }
    SetEvent(event);
 
    WaitForSingleObject(end, INFINITE);
    int m;
    DWORD sz;
    ReadFile(read, &m, sizeof(m), &sz, NULL);
    short* h = new short[m];
    for (int i = 0; i < m; i++) {
        DWORD size;
        ReadFile(read, &h[i], sizeof(h[i]), &size, NULL);
    }
    for (int i = 0; i < m; i++) {
        cout << h[i]<<" ";
    }
}


