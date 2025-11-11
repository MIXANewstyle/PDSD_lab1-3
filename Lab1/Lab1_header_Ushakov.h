#pragma once

#include <string>
#include <sstream>
#include <random>

// Структура для узла (остается без изменений)
struct Node {
    int data;
    Node* next;
};

// Класс "Множество"
class MySet {
private:
    // --- Параметр класса ---
    Node* _head; // Указатель на голову списка

    // --- Вспомогательный метод (нужен для F5) ---
    int getRandomInt(int minVal, int maxVal);

public:
    // --- Методы класса (F1-F14) ---

    // F1. Конструктор по умолчанию (создание пустого множества)
    MySet();

    // F5. Параметризованный конструктор (создание множества)
    MySet(int count, int minVal, int maxVal, char setRule = ' ');

    // F8. Деструктор (удаление множества)
    ~MySet();

    // F2. Пустое множество? (const - не изменяет объект)
    bool IsEmpty() const;

    // F3. Проверка принадлежности (const - не изменяет объект)
    bool IsInSet(int value) const;

    // F4. Добавление элемента
    // (Возвращает bool, чтобы F5 мог понять, был ли элемент добавлен)
    bool AddElement(int value);

    // F6. Мощность множества (const - не изменяет объект)
    int GetPower() const;

    // F7. Вывод в строку (const - не изменяет объект)
    std::string GetSetAsString(char separator) const;

    // F9. Подмножество? (const - не изменяет 'this')
    bool IsSubset(const MySet& otherSet) const;

    // F10. Равенство? (const - не изменяет 'this')
    bool IsEqual(const MySet& otherSet) const;

    // F11. Объединение (const - не изменяет 'this' и 'otherSet')
    // Возвращает НОВЫЙ объект MySet
    MySet Union(const MySet& otherSet) const;

    // F12. Пересечение (const)
    MySet Intersection(const MySet& otherSet) const;

    // F13. Разность (const)
    MySet Difference(const MySet& otherSet) const;

    // F14. Симметричная разность (const)
    MySet SymmetricDifference(const MySet& otherSet) const;
};