#include <iostream>
#include "deque.h"
#include <cstring>
#include <iomanip>
#include <string>

int main() {
    containers::deque<const char*> deq;
    std::cout << "enter the number to function:\n";
    std::cout << "1. PushBack\n2. PushFront\n3. Size\n4. PopFront\n5. PopBack\n6. Head\n7. Tail\n";
    std::cout << "8. Cout from Head to Tail\n9. Cout from Tail to Head\n10. Exit\n";
    while (true) {
        int temp;
        char* b = new char[70];
        std::cin >> temp;
        switch (temp) {
        case 1:
            std::cin >> b;
            deq.PushBack(b);
            break;
        case 2:
            std::cin >> b;
            deq.PushFront(b);
            break;
        case 3:
            std::cout << deq.Size();
            break;
        case 4:
            deq.PopFront();
            break;
        case 5:
            deq.PopBack();
            break;
        case 6:
            std::cout << deq.Front()->value << std::endl;
            break;
        case 7:
            std::cout << deq.Back()->value << std::endl;
            break;
        case 8:
            deq.WriteToConsoleFromHeadToTail();
            break;
        case 9:
            deq.WriteToConsoleFromTailToHead();
            break;
        case 10:
            std::cout << "The program is finished\n";
            return 0;
        }
    }
}
