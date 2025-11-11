#include <iostream>
#include <string>
#include <clocale>      // для setlocale
#include <random>       // для генерации размера
#include <iomanip>      // для boolalpha (вывод true/false)

// Подключаем наш заголовочный файл со всеми функциями
#include "Lab1_header_Ushakov.h" 

// Используем пространства имен
using namespace std;

// Глобальный генератор для main (чтобы получить размер)
int GetRandomInt(int minVal, int maxVal) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(minVal, maxVal);
    return dist(gen);
}


int main() {
    // Устанавливаем русскую локаль для консоли
    setlocale(LC_ALL, "Russian");
    // Устанавливаем вывод true/false вместо 1/0
    cout << boolalpha;

    cout << "--- Тестирование функций F9-F14 ---" << endl;

    // 1. Создание исходных данных
    int sizeA = GetRandomInt(6, 9);
    int sizeB = GetRandomInt(6, 9);

    cout << "Генерация множеств A и B..." << endl;

    // Создаем множества (двузначные 10-99)
    // Диапазоны пересекаются (A: 10-70, B: 50-99), 
    // чтобы пересечение не было пустым (требование)
    Node* setA = F5_CreateSet(sizeA, 10, 70);
    Node* setB = F5_CreateSet(sizeB, 50, 99);

    cout << "Мощность A: " << F6_GetPower(setA) << endl;
    cout << "Множество A: " << F7_GetSetAsString(setA, ',') << endl;
    cout << "Мощность B: " << F6_GetPower(setB) << endl;
    cout << "Множество B: " << F7_GetSetAsString(setB, ',') << endl;

    // 2. Тестирование

    cout << "\n--- Тест F9 (Подмножество) ---" << endl;
    cout << "  A является подмножеством B? -> " << F9_IsSubset(setA, setB) << endl;
    cout << "  A является подмножеством A? -> " << F9_IsSubset(setA, setA) << endl; // Тест A ⊂ A

    cout << "\n--- Тест F10 (Равенство) ---" << endl;
    cout << "  A равно B? -> " << F10_IsEqual(setA, setB) << endl;
    cout << "  A равно A? -> " << F10_IsEqual(setA, setA) << endl; // Тест A = A

    cout << "\n--- Тест F11 (Объединение) ---" << endl;
    Node* setUnion = F11_Union(setA, setB);
    cout << "  Объединение (A U B): " << F7_GetSetAsString(setUnion, ',') << endl;

    cout << "\n--- Тест F12 (Пересечение) ---" << endl;
    Node* setInter = F12_Intersection(setA, setB);
    cout << "  Пересечение (A и B): " << F7_GetSetAsString(setInter, ',') << endl;

    cout << "\n--- Тест F13 (Разность) ---" << endl;
    // Тест A - B
    Node* setDiffAB = F13_Difference(setA, setB);
    cout << "  Разность (A \\ B): " << F7_GetSetAsString(setDiffAB, ',') << endl;
    // Тест B - A
    Node* setDiffBA = F13_Difference(setB, setA);
    cout << "  Разность (B \\ A): " << F7_GetSetAsString(setDiffBA, ',') << endl;

    cout << "\n--- Тест F14 (Симметричная разность) ---" << endl;
    Node* setSymDiff = F14_SymmetricDifference(setA, setB);
    cout << "  Симм. разность (A и B): " << F7_GetSetAsString(setSymDiff, ',') << endl;


    // 3. Очистка памяти
    cout << "\n--- Очистка памяти (F8) ---" << endl;
    setA = F8_DeleteSet(setA);
    setB = F8_DeleteSet(setB);
    // Очищаем все множества-результаты
    setUnion = F8_DeleteSet(setUnion);
    setInter = F8_DeleteSet(setInter);
    setDiffAB = F8_DeleteSet(setDiffAB);
    setDiffBA = F8_DeleteSet(setDiffBA);
    setSymDiff = F8_DeleteSet(setSymDiff);
    cout << "Вся память очищена." << endl;

    return 0;
}