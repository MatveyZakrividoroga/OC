#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<Windows.h>
#include<conio.h>
#include <set>
using namespace std;

int main(int argc, char* argv[])
{
    HANDLE end = OpenEvent(EVENT_ALL_ACCESS, FALSE, "end");
    HANDLE write = (HANDLE)atoi(argv[1]);
    HANDLE read = (HANDLE)atoi(argv[2]);
    HANDLE event = OpenEvent(SYNCHRONIZE, FALSE, "1");
    if (event == NULL) {
        GetLastError();
    }
    WaitForSingleObject(event, INFINITE);
    cout << "Enter N,M\n";
    int M, N;
    cin >> N>>M;
    int n = atoi(argv[3]);
    short* ar = new short[n];
    for (int i = 0; i < atoi(argv[3]); i++) {
        DWORD s;
        ReadFile(read, &ar[i], sizeof(ar[i]), &s, NULL);
    }
    for (int i = 0; i < atoi(argv[3]); i++) {
        cout << ar[i]<<" ";
    }
    int ind=0;
    cout << '\n';
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
    
    DWORD sz;
    WriteFile(write, &ind, sizeof(ind), &sz, NULL);

    for (size_t i = 0; i < ind; i++)
    {
        DWORD r;
        WriteFile(write, &ar1[i], sizeof(ar1[i]), &r, NULL);

    }
    for (size_t i = 0; i < ind; i++) {
        cout << ar1[i] << " ";
    }
    SetEvent(end);
    int kostyl;
    cin >> kostyl;
}


