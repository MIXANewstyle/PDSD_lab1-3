#include <iostream>
#include "Lab_1_header_Ipatov.h"



int main()
{
    setlocale(LC_ALL, "Russian");
    int size = getRandomInt(6, 9);
    Node* A = createNewSet(size, 1, 100);
    cout << "Создано множество А -> " << printSet(A, "|") << endl;
    cout << "Мощность множества A -> " << getPowerOfSet(A) << endl;
    cout << "Вывод множества А -> " << printSet(A, "|") << endl;
    A = deleteSet(A);
    cout << "Удаление множества А " << endl;
    cout << "Мощность множества A -> " << getPowerOfSet(A) << endl;
    cout << "Вывод множества А -> " << printSet(A, "|") << endl;
}

