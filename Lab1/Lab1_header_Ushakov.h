#pragma once

// Подключаем необходимые библиотеки для реализации
#include <string>       
#include <sstream>      
#include <random>       

// Структура для узла односвязного списка
struct Node {
    int data;       // Полезная информация (значение элемента)
    Node* next;     // Указатель на следующий узел
};


// F1. Создание пустого множества
Node* F1_CreateEmptySet();

// F2. Пустое множество?
bool F2_IsEmpty(Node* head);

// F3. Проверка принадлежности элемента множеству
bool F3_IsInSet(Node* head, int value);

// F4. Добавление нового элемента в множество
Node* F4_AddElement(Node* head, int value);

// F5. Создание множества
// Добавлен char setRule: 'A' (кратные 9), 'B' (кратные 3), иначе - любое
Node* F5_CreateSet(int count, int minVal, int maxVal, char setRule);

// F6. Мощность множества
int F6_GetPower(Node* head);

// F7. Вывод элементов множества в строку
std::string F7_GetSetAsString(Node* head, char separator);

// F8. Удаление множества (очистка памяти)
Node* F8_DeleteSet(Node* head);


//   (Лабораторная 2) 

// F9. Подмножество (A является подмножеством B?)
// (Использует F2, F3)
bool F9_IsSubset(Node* headA, Node* headB);

// F10. Равенство двух множеств (A == B?)
// (Использует F9)
bool F10_IsEqual(Node* headA, Node* headB);

// F11. Объединение двух множеств (A U B)
// (Использует F2, F4)
Node* F11_Union(Node* headA, Node* headB);

// F12. Пересечение двух множеств (A ∩ B)
// (Использует F2, F4, F3)
Node* F12_Intersection(Node* headA, Node* headB);

// F13. Разность множеств (A \ B)
// (Использует F2, F4, F3)
Node* F13_Difference(Node* headA, Node* headB);

// F14. Симметричная разность (A Δ B)
// (Использует F11, F12, F13)
Node* F14_SymmetricDifference(Node* headA, Node* headB);