#include "Lab_1_header_Ipatov.h"

//F1
Node* createEmptySet()
{
	return nullptr;
}

//F2
bool isEmpty(Node* elem)
{
	return elem == nullptr;
}

//F3
Node* addToBegin(Node* firstElem, int valueOfElem)
{
	if (isInSet(firstElem, valueOfElem)) {
		return firstElem;
	}
	Node* a = firstElem;
	Node* newElem = new Node(valueOfElem);
	newElem->next = a;
	return newElem;
}

//F4
Node* createNewSet(int countOfElements, int minValue, int maxValue)
{
	Node* head = new Node(getRandomInt(minValue, maxValue));

	int i = 0;
	while (i < countOfElements)
	{
		Node* oldHead = head;
		head = addToBegin(head, getRandomInt(minValue, maxValue));
		if (oldHead != head) {
			i++;
		}
	}

	return head;
}

//F5
string printSet(Node* firstElem, string separator)
{
	if (!isEmpty(firstElem)) {
		stringstream streamStr;
		Node* current = firstElem;

		while (current != nullptr)
		{
			streamStr << current->val;
			streamStr << separator;
			current = current->next;
		}
		string result = streamStr.str();
		result.pop_back();
		return result;
	}
	return "Множество пустое!";

}

//F6
bool isInSet(Node* firstElem, int valueOfElem)
{
	Node* current = firstElem;

	if (isEmpty(firstElem)) { return false; }

	do
	{
		if (valueOfElem != current->val)
		{
			current = current->next;
		}
		else { return true; }

	} while (current != nullptr);

	return false;
}

//F7
int getPowerOfSet(Node* firstElem)
{
	int value = 0;
	Node* current = firstElem;
	
	if (isEmpty(firstElem)) { return value; }

	do
	{
		value++;
		current = current->next;

	} while (current != nullptr);

	return value;
}


int getRandomInt(int minValue, int maxValue) {
	random_device rd;  // Источник случайных чисел (аппаратный)
	mt19937 gen(rd());  // Генератор случайных чисел (Mersenne Twister)
	uniform_int_distribution<> dist(minValue, maxValue);  // Распределение от 10 до 20
	int randomValue = dist(gen);
	return randomValue;
}

//F8
Node* deleteSet(Node* firstElem)
{
	int count = getPowerOfSet(firstElem);
	Node* current = firstElem;

	while (current != nullptr) {
		Node* next = current->next;
		delete current;
		current = next;
	}

	return nullptr;
}


//F9
bool isUnderSet(Node* underSet, Node* set)
{
	if (isEmpty(underSet)) return true;
	if (underSet == set) return true;
	
	Node* currentUnder = underSet;
	do 
	{
		if (isInSet(set, currentUnder->val)) {
			currentUnder = currentUnder->next;
		}
		else return false;
		
	} while (currentUnder->next != nullptr);

	return true;
}

//F10
bool isEqualitySets(Node* firstElemA, Node* firstElemB) 
{
	return isUnderSet(firstElemA, firstElemB) && isUnderSet(firstElemB, firstElemA);
}
