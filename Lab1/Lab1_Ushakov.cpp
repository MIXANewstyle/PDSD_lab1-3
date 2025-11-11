#include "Lab1_header_Ushakov.h"
#include <iostream>


using namespace std;

// --- Вспомогательный метод ---
int MySet::getRandomInt(int minVal, int maxVal) {
    // static, чтобы генератор инициализировался один раз
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dist(minVal, maxVal);
    return dist(gen);
}

// --- F1. Конструктор по умолчанию ---
MySet::MySet() {
    _head = nullptr; // Логика F1_CreateEmptySet
}

// --- F5. Параметризованный конструктор ---
MySet::MySet(int count, int minVal, int maxVal, char setRule) {
    _head = nullptr; // Начинаем с пустого множества

    // Проверка возможности создания (логика из старой F5)
    int availableCount = 0;
    for (int i = minVal; i <= maxVal; ++i) {
        if (setRule == 'A' && i % 9 == 0) availableCount++;
        else if (setRule == 'B' && i % 3 == 0) availableCount++;
        else if (setRule != 'A' && setRule != 'B') availableCount++;
    }

    if (count > availableCount) {
        cerr << "Ошибка F5: Невозможно создать множество. "
            << "Требуемое кол-во (" << count
            << ") > чем доступно (" << availableCount << ")" << endl;
        return; // _head остается nullptr (пустое множество)
    }

    // Цикл генерации
    int elementsAdded = 0;
    int attempts = 0;
    int maxAttempts = count * 150 + 1000;

    while (elementsAdded < count && attempts < maxAttempts) {
        int randomValue = getRandomInt(minVal, maxVal);
        attempts++;

        // Проверяем правило
        bool passesRule = false;
        if (setRule == 'A') passesRule = (randomValue % 9 == 0);
        else if (setRule == 'B') passesRule = (randomValue % 3 == 0);
        else passesRule = true;

        if (passesRule) {
            // Используем метод AddElement (F4)
            // Он вернет true, если элемент был НОВЫМ
            if (this->AddElement(randomValue)) {
                elementsAdded++;
            }
        }
    }
}

// --- F8. Деструктор ---
MySet::~MySet() {
    // Логика из F8_DeleteSet
    Node* current = _head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp; // Освобождаем память
    }
    _head = nullptr;
}

// --- F2. Пустое множество? ---
bool MySet::IsEmpty() const {
    return _head == nullptr; // Логика F2
}

// --- F3. Проверка принадлежности ---
bool MySet::IsInSet(int value) const {
    if (this->IsEmpty()) { // Используем F2
        return false;
    }
    Node* current = _head;
    while (current != nullptr) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false; // Логика F3
}

// --- F4. Добавление элемента ---
bool MySet::AddElement(int value) {
    if (this->IsInSet(value)) { // Используем F3
        return false; // Элемент уже есть, не добавлен
    }

    // Логика F4
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = _head; // Добавление в начало
    _head = newNode;
    return true; // Элемент успешно добавлен
}

// --- F6. Мощность множества ---
int MySet::GetPower() const {
    if (this->IsEmpty()) { // Используем F2
        return 0;
    }
    int count = 0;
    Node* current = _head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count; // Логика F6
}

// --- F7. Вывод в строку ---
string MySet::GetSetAsString(char separator) const {
    if (this->IsEmpty()) { // Используем F2
        return "Множество пустое";
    }

    stringstream ss;
    Node* current = _head;
    while (current != nullptr) {
        ss << current->data;
        if (current->next != nullptr) {
            ss << separator;
        }
        current = current->next;
    }
    return ss.str(); // Логика F7
}

// --- F9. Подмножество? ---
bool MySet::IsSubset(const MySet& otherSet) const {
    if (this->IsEmpty()) { // F2
        return true;
    }

    // Проверяем, что КАЖДЫЙ элемент 'this' (A) есть в 'otherSet' (B)
    Node* currentA = _head;
    while (currentA != nullptr) {
        // Используем F3 другого объекта!
        if (!otherSet.IsInSet(currentA->data)) {
            return false;
        }
        currentA = currentA->next;
    }
    return true; // Логика F9
}

// --- F10. Равенство? ---
bool MySet::IsEqual(const MySet& otherSet) const {
    // Логика F10: A == B, если (A ⊂ B) и (B ⊂ A)
    // Используем F9
    return this->IsSubset(otherSet) && otherSet.IsSubset(*this);
}

// --- F11. Объединение ---
MySet MySet::Union(const MySet& otherSet) const {
    MySet result; // Создается ПУСТОЕ множество (сработал F1)

    // Добавляем все из 'this' (A)
    Node* currentA = _head;
    while (currentA != nullptr) {
        result.AddElement(currentA->data); // F4
        currentA = currentA->next;
    }

    // Добавляем все из 'otherSet' (B)
    // Мы можем получить доступ к _head, т.к. мы - метод того же класса
    Node* currentB = otherSet._head;
    while (currentB != nullptr) {
        result.AddElement(currentB->data); // F4 (сама проверит дубликат)
        currentB = currentB->next;
    }

    return result; // Возвращаем НОВЫЙ объект
}

// --- F12. Пересечение ---
MySet MySet::Intersection(const MySet& otherSet) const {
    MySet result; // F1

    if (this->IsEmpty() || otherSet.IsEmpty()) { // F2
        return result;
    }

    // Идем по 'this' (A)
    Node* currentA = _head;
    while (currentA != nullptr) {
        // Если элемент A есть в B (F3)
        if (otherSet.IsInSet(currentA->data)) {
            result.AddElement(currentA->data); // Добавляем в результат (F4)
        }
        currentA = currentA->next;
    }

    return result;
}

// --- F13. Разность ---
MySet MySet::Difference(const MySet& otherSet) const {
    MySet result; // F1

    if (this->IsEmpty()) { // F2
        return result;
    }

    // Идем по 'this' (A)
    Node* currentA = _head;
    while (currentA != nullptr) {
        // Если элемент A НЕту в B (F3)
        if (!otherSet.IsInSet(currentA->data)) {
            result.AddElement(currentA->data); // Добавляем в результат (F4)
        }
        currentA = currentA->next;
    }

    return result;
}

// --- F14. Симметричная разность ---
MySet MySet::SymmetricDifference(const MySet& otherSet) const {

    // (A U B)
    MySet tempUnion = this->Union(otherSet); // F11

    // (A ∩ B)
    MySet tempIntersection = this->Intersection(otherSet); // F12

    // (A U B) \ (A ∩ B)
    MySet result = tempUnion.Difference(tempIntersection); // F13

    return result;

    // Временные объекты tempUnion и tempIntersection
    // будут УДАЛЕНЫ АВТОМАТИЧЕСКИ (вызовется F8)!
}