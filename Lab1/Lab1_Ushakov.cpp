#include "Lab1_header_Ushakov.h"
#include <iostream> 

using namespace std;

// F1. Создание пустого множества
Node* F1_CreateEmptySet() {
    return nullptr;
}

// F2. Пустое множество?
bool F2_IsEmpty(Node* head) {
    return head == nullptr;
}

// F3. Проверка принадлежности элемента множеству
bool F3_IsInSet(Node* head, int value) {
    if (F2_IsEmpty(head)) { // Используем F2
        return false;
    }
    Node* current = head;
    while (current != nullptr) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// F4. Добавление нового элемента в множество
Node* F4_AddElement(Node* head, int value) {
    if (F3_IsInSet(head, value)) { // Используем F3
        return head;
    }
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = head;
    return newNode;
}

// F5. Создание множества 
Node* F5_CreateSet(int count, int minVal, int maxVal, char setRule) {

    // Проверка возможности создания
    int availableCount = 0;
    for (int i = minVal; i <= maxVal; ++i) {
        if (setRule == 'A' && i % 9 == 0) {
            availableCount++;
        }
        else if (setRule == 'B' && i % 3 == 0) {
            availableCount++;
        }
        else if (setRule != 'A' && setRule != 'B') {
            availableCount++; // Общий случай (любое число)
        }
    }

    // Если в заданном диапазоне нет 'availableCount' чисел по правилу,
    // то создать множество из 'count' УНИКАЛЬНЫХ элементов невозможно.
    if (count > availableCount) {
        cerr << "Ошибка F5: Невозможно создать множество. "
            << "Требуемое кол-во (" << count
            << ") > чем доступно по правилу (" << availableCount << ")" << std::endl;
        return F1_CreateEmptySet();
    }

    // Настройка генератора
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dist(minVal, maxVal);

    Node* head = F1_CreateEmptySet();
    int elementsAdded = 0;

    // Цикл генерации
    // Добавим защиту от слишком долгого поиска
    int maxAttempts = count * 150 + 1000; // Попыток, чтобы найти числа
    int attempts = 0;

    while (elementsAdded < count && attempts < maxAttempts) {
        int randomValue = dist(gen);
        attempts++;

        // Проверяем, подходит ли число по правилу
        bool passesRule = false;
        if (setRule == 'A') {
            passesRule = (randomValue % 9 == 0);
        }
        else if (setRule == 'B') {
            passesRule = (randomValue % 3 == 0);
        }
        else {
            passesRule = true; // Любое число подходит
        }

        // Если подошло, пытаемся добавить (F4 проверит на дубликат)
        if (passesRule) {
            Node* newHead = F4_AddElement(head, randomValue);
            if (head != newHead) { // F4 добавила новый элемент
                elementsAdded++;
                head = newHead;
            }
        }
    }

    if (attempts >= maxAttempts && elementsAdded < count) {
        cerr << "Предупреждение F5: Превышено кол-во попыток. "
            << "Множество может быть неполным (создано "
            << elementsAdded << " из " << count << ")." << endl;
    }

    return head;
}

// F6. Мощность множества
int F6_GetPower(Node* head) {
    if (F2_IsEmpty(head)) { // Используем F2
        return 0;
    }
    int count = 0;
    Node* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

// F7. Вывод элементов множества в строку
std::string F7_GetSetAsString(Node* head, char separator) {
    if (F2_IsEmpty(head)) { // Используем F2
        return "Множество пустое";
    }
    std::stringstream ss;
    Node* current = head;
    while (current != nullptr) {
        ss << current->data;
        if (current->next != nullptr) {
            ss << separator;
        }
        current = current->next;
    }
    return ss.str();
}

// F8. Удаление множества (очистка памяти)
Node* F8_DeleteSet(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    return nullptr;
}

// (Лабораторная 2) 

// F9. Подмножество (A является подмножеством B?)
bool F9_IsSubset(Node* headA, Node* headB) {
    // 1. Пустое множество (A) является подмножеством любого (B)
    if (F2_IsEmpty(headA)) { // Используем F2
        return true;
    }

    // 2. Если A не пустое, а B пустое, то A не подмножество B
    if (F2_IsEmpty(headB)) {
        return false;
    }

    // 3. Общий случай: проверяем, что КАЖДЫЙ элемент из A есть в B
    Node* currentA = headA;
    while (currentA != nullptr) {
        // Используем F3 (которая внутри использует F2)
        if (!F3_IsInSet(headB, currentA->data)) {
            // Нашли элемент A, которого нет в B
            return false;
        }
        currentA = currentA->next;
    }

    // Если цикл завершился, все элементы A найдены в B
    return true;
}

// F10. Равенство двух множеств (A == B?)
bool F10_IsEqual(Node* headA, Node* headB) {
    // Множества равны, если (A ⊂ B) и (B ⊂ A)
    // Используем F9
    return F9_IsSubset(headA, headB) && F9_IsSubset(headB, headA);
}

// F11. Объединение двух множеств (A U B)
Node* F11_Union(Node* headA, Node* headB) {
    Node* result = F1_CreateEmptySet();

    // Добавляем все элементы из A
    Node* currentA = headA;
    if (!F2_IsEmpty(currentA)) { // Проверка F2
        while (currentA != nullptr) {
            result = F4_AddElement(result, currentA->data); // Используем F4
            currentA = currentA->next;
        }
    }

    // Добавляем все элементы из B
    Node* currentB = headB;
    if (!F2_IsEmpty(currentB)) { // Проверка F2
        while (currentB != nullptr) {
            result = F4_AddElement(result, currentB->data); // F4 сама позаботится о дубликатах
            currentB = currentB->next;
        }
    }

    return result; // Возвращаем новое множество
}

// F12. Пересечение двух множеств (A ∩ B)
Node* F12_Intersection(Node* headA, Node* headB) {
    // Если одно из множеств пустое, пересечение пусто
    if (F2_IsEmpty(headA) || F2_IsEmpty(headB)) { // Используем F2
        return F1_CreateEmptySet();
    }

    Node* result = F1_CreateEmptySet();
    Node* currentA = headA;

    // Идем по A и проверяем, есть ли элемент в B
    while (currentA != nullptr) {
        if (F3_IsInSet(headB, currentA->data)) {
            // Элемент есть в обоих, добавляем в результат
            result = F4_AddElement(result, currentA->data); // Используем F4
        }
        currentA = currentA->next;
    }

    return result;
}

// F13. Разность множеств (A \ B)
Node* F13_Difference(Node* headA, Node* headB) {
    // Если A пустое, разность (A \ B) пустая
    if (F2_IsEmpty(headA)) { // Используем F2
        return F1_CreateEmptySet();
    }

    Node* result = F1_CreateEmptySet();
    Node* currentA = headA;

    // Идем по A и ищем элементы, которых НЕТ в B
    while (currentA != nullptr) {
        if (!F3_IsInSet(headB, currentA->data)) {
            // Элемент есть в A, но нет в B
            result = F4_AddElement(result, currentA->data); // Используем F4
        }
        currentA = currentA->next;
    }

    return result;
}

// F14. Симметричная разность (A Δ B)
Node* F14_SymmetricDifference(Node* headA, Node* headB) {
    // Используем определение: (A U B) \ (A ∩ B)
    // Это позволяет использовать F11, F12 и F13, как требует задание.

    // 1. Находим (A U B)
    Node* tempUnion = F11_Union(headA, headB);

    // 2. Находим (A ∩ B)
    Node* tempIntersection = F12_Intersection(headA, headB);

    // 3. Находим разность (U \ I)
    Node* result = F13_Difference(tempUnion, tempIntersection);

    // 4. Очищаем память, занятую временными множествами
    F8_DeleteSet(tempUnion);
    F8_DeleteSet(tempIntersection);

    return result;
}