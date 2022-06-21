#include<conio.h>
#include <iostream>
#include<Windows.h>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
int main()
{
  //  char lpszAppName[] =  "C:\\Users\\Witumm\\source\\repos\\OC(2)\\Debug\\Child.exe";//"Child.exe";
    char lpszAppName[] = "Child.exe";//"Child.exe";
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags = STARTF_USEFILLATTRIBUTE;
    si.dwFillAttribute = FOREGROUND_RED;
    int n;
    cout << "Enter array size:";
    cin >> n;
    string str="";
    string tmp="";
    cout << "Enter array elements:";
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        str += tmp;
        str += " ";
    }
    char* h = new char[str.length()];
    for (int i = 0; i < str.length()-1; i++) {
        h[i] = str[i];
    }
    /*for (int i=0; i < str.length()-1; i++) {
        cout << h[i];
    }*/
    if (!CreateProcess(lpszAppName, h, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi)) {
        _cputs("Invalid process");
        return 0;
    }

    _cputs("Process created");
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

}
