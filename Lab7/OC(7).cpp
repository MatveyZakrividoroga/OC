#include <iostream>
#include<Windows.h>
class MonitorQueuer {
public:
    MonitorQueuer(int sizeN) :size(sizeN), addPos(sizeN - 1), removePos(sizeN - 1) {
        ProduceSem = CreateSemaphore(NULL, size, size, "produce");
        ConsumeSem = CreateSemaphore(NULL, 0, size, "consume");
        arr = new int[size];
    }
    ~MonitorQueuer() {
        CloseHandle(ProduceSem);
        CloseHandle(ConsumeSem);
        delete[] arr;
    }
    void AddHead(int a) {
        WaitForSingleObject(ProduceSem, INFINITE);
        arr[addPos] = a;
        addPos--;
        if (addPos == -1) {
            addPos = size - 1;
        }
        ReleaseSemaphore(ConsumeSem, 1, NULL);
    }
    int RemoveTail() {
        WaitForSingleObject(ConsumeSem, INFINITE);
        removePos--;
        if (removePos == -2) {
            removePos = size - 2;
        }
        ReleaseSemaphore(ProduceSem, 1, NULL);
        return arr[removePos + 1];
    }


private:
    int* arr;
    int size, addPos, removePos;
    HANDLE ProduceSem, ConsumeSem;
};
struct str {
    MonitorQueuer* queue;
    int a;
    int b;

};
HANDLE ac = CreateSemaphore(NULL, 1, 1, "acsess");
DWORD Produce(str* st) {

    char s[80];
    for (int i = 0; i < st->a; i++) {
        WaitForSingleObject(ac, INFINITE);
        st->queue->AddHead(st->b);
        wsprintf(s, "Produce product %d\n", st->b);
        std::cout << s;
        ReleaseSemaphore(ac, 1, NULL);
    }

    return 0;
}
DWORD Consume(str* st) {
    int tmp;
    char s[80];
    for (int i = 0; i < st->a; i++) {

        tmp = st->queue->RemoveTail();
        wsprintf(s, "Consume product %d\n", tmp);
        std::cout << s;
        ReleaseSemaphore(ac, 1, NULL);
    }
    return 0;
}
int main()
{
    int n;
    MonitorQueuer* que;
    std::cout << "Input size of queue\n";
    std::cin >> n;
    que = new MonitorQueuer(n);
    std::cout << "Input number of consume & produce process\n";
    int a, b;
    std::cin >> a >> b;
    str* cons = new str[a];
    str* prod = new str[b];
    int tmp;
    for (int i = 0; i < b; i++) {
        prod[i].queue = que;
        std::cout << "Input number of produce products\n";
        std::cin >> prod[i].a;
        std::cout << "Input product\n";
        std::cin >> prod[i].b;

    }
    for (int i = 0; i < a; i++) {
        cons[i].queue = que;
        std::cout << "Input number of consume products\n";
        std::cin >> cons[i].a;
    }

    HANDLE* produce = new HANDLE[b];
    HANDLE* consume = new HANDLE[a];
    DWORD ID;
    for (int i = 0; i < b; i++) {
        produce[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Produce, &prod[i], 0, &ID);
    }
    for (int i = 0; i < a; i++) {
        consume[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Consume, &cons[i], 0, &ID);
    }
    WaitForMultipleObjects(b, produce, TRUE, INFINITE);
    WaitForMultipleObjects(a, consume, TRUE, INFINITE);
}
