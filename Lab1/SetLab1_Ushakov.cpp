#include "Lab1_header_Ushakov.h"
#include <iostream> // Для вывода ошибки в F5

// F1. Создание пустого множества
Node* F1_CreateEmptySet() {
    return nullptr; // Пустое множество - это просто NULL-указатель
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
            return true; // Нашли элемент
        }
        current = current->next;
    }
    return false; // Не нашли
}

// F4. Добавление нового элемента в множество
Node* F4_AddElement(Node* head, int value) {
    // Множество не хранит дубликаты
    if (F3_IsInSet(head, value)) { // Используем F3
        return head; // Элемент уже есть, возвращаем список без изменений
    }

    // Создаем новый узел
    Node* newNode = new Node;
    newNode->data = value;
    // Добавляем в начало списка
    newNode->next = head;

    // Новый узел теперь является головой списка
    return newNode;
}

// F5. Создание множества
Node* F5_CreateSet(int count, int minVal, int maxVal) {
    // Проверка возможности создания (требование)
    int rangeSize = maxVal - minVal + 1;
    if (count > rangeSize) {
        // Невозможно создать множество из 'count' УНИКАЛЬНЫХ элементов
        // в заданном диапазоне.
        std::cerr << "Ошибка F5: Невозможно создать множество. "
            << "Требуемое кол-во (" << count
            << ") > чем диапазон (" << rangeSize << ")" << std::endl;
        return F1_CreateEmptySet(); // Возвращаем пустое множество
    }

    // Настройка генератора случайных чисел
    // (static, чтобы инициализироваться только один раз)
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(minVal, maxVal);

    Node* head = F1_CreateEmptySet(); // Начинаем с пустого множества
    int elementsAdded = 0;

    // Цикл, пока не добавим нужное кол-во УНИКАЛЬНЫХ элементов
    while (elementsAdded < count) {
        int randomValue = dist(gen);

        // F4 сама проверит на дубликат (через F3)
        Node* newHead = F4_AddElement(head, randomValue); // Используем F4

        if (head != newHead) { // Если F4 добавила новый элемент
            elementsAdded++;
            head = newHead; // Обновляем голову списка
        }
        // Если head == newHead, значит был сгенерирован дубликат,
        // F4 его не добавила, и elementsAdded не увеличился.
        // Цикл продолжится.
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
        // Требование: в конце строки разделитель стоять не должен
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
        Node* temp = current;      // Сохраняем узел для удаления
        current = current->next; // Переходим к следующему
        delete temp;             // Освобождаем память
    }
    // ВАЖНО: Твой деструктор и DeleteSet в наработках были некорректны,
    // они не освобождали память (delete), а просто сбрасывали указатели.

    return nullptr; // Возвращаем NULL, как требует задание
}