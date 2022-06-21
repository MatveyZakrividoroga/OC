
#include<Windows.h>
#include<conio.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
   
   
    char* arr = new char[argc];
    string s;
    for (int i = 0; i < argc; i++) {

        s += argv[i];
    
    }
    for (int i = 0; i < argc; i++) {
        cout << s[i] << ' ';
    }

    int el;
    int t;
    for (int i = 0; i < argc; i++) {
        for (int j = i + 1; j < argc; j++) {
            if (s[i] == s[j]) {
                char temp;
                temp = s[i + 1];
                s[i + 1] = s[j];
                s[j] = temp;
            }
        }
    }
    cout << '\n';

    for (int i = 0; i < argc; i++) {
        cout << s[i] << ' ';
    }
   
    _getch();
  
}
