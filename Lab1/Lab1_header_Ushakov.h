#pragma once


#include <iostream>
#include <string>
#include <clocale>      
#include <random>
#include <sstream>

using namespace std;
// Структура для узла односвязного списка
struct Node {
    int data;       // значение элемента
    Node* next;     // Указатель на следующий узел
};

// F1. Создание пустого множества
Node* F1_CreateEmptySet();

// F2. Пустое множество?
bool F2_IsEmpty(Node* head);

// F3. Проверка принадлежности элемента множеству
// (Использует F2)
bool F3_IsInSet(Node* head, int value);

// F4. Добавление нового элемента в множество
// (Использует F3, добавление в начало)
Node* F4_AddElement(Node* head, int value);

// F5. Создание множества
// (Использует F4, проверяет возможность создания)
Node* F5_CreateSet(int count, int minVal, int maxVal);

// F6. Мощность множества
// (Использует F2)
int F6_GetPower(Node* head);

// F7. Вывод элементов множества в строку
// (Использует F2, без разделителя в конце)
string F7_GetSetAsString(Node* head, char separator);

// F8. Удаление множества (очистка памяти)
Node* F8_DeleteSet(Node* head);