


#include "Lab1_header_Ushakov.h" 

using namespace std;

// Глобальный генератор для main (чтобы получить размер)
// (F5 использует свой собственный)
int GetRandomInt(int minVal, int maxVal) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(minVal, maxVal);
    return dist(gen);
}


int main() {
    // Устанавливаем русскую локаль для консоли
    setlocale(LC_ALL, "Russian");

    // Задаем требуемый размер от 6 до 9
    int size = GetRandomInt(6, 9);

    cout << "--- Тестирование функций F5, F6, F7, F8 ---" << endl;
    cout << "Требуемый размер множества (от 6 до 9): " << size << endl;

    // 1. Тестируем F5 (Создание)
    // Создаем множество A из 'size' элементов в диапазоне [1, 100]
    Node* setA = F5_CreateSet(size, 1, 100);
    cout << "\n[Тест F5] Множество A создано." << endl;

    // 2. Тестируем F7 (Вывод)
    cout << "[Тест F7] Элементы множества A: "
        << F7_GetSetAsString(setA, '|') << endl;

    // 3. Тестируем F6 (Мощность)
    cout << "[Тест F6] Мощность множества A: "
        << F6_GetPower(setA) << endl;

    // 4. Тестируем F8 (Удаление)
    cout << "\n[Тест F8] Удаление множества A..." << endl;
    setA = F8_DeleteSet(setA); // Функция вернет nullptr
    cout << "Множество A удалено (setA теперь "
        << (setA == nullptr ? "NULL" : "НЕ NULL") << ")." << endl;

    // 5. Повторная проверка F6 и F7 на пустом множестве
    cout << "\n--- Повторная проверка на удаленном множестве ---" << endl;

    cout << "[Тест F6] Мощность A после удаления: "
        << F6_GetPower(setA) << endl;

    cout << "[Тест F7] Вывод A после удаления: "
        << F7_GetSetAsString(setA, '|') << endl;

    cout << "\n--- Тестирование завершено ---" << endl;

    return 0;
}