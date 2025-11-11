#pragma once

#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <random>

using namespace std;

struct Node
{
	int val;
	Node *next = nullptr;
	Node(int _val) : val(_val), next(nullptr) {}
};

Node *createEmptySet();

bool isEmpty(Node *elem);

bool isInSet(Node *firstElem, int valueOfElem);

Node *addToBegin(Node *, int);

Node *createNewSet(int countOfElements, int minValue, int maxValue);

int getPowerOfSet(Node *firstElem);

string printSet(Node *firstElem, string separator);

Node *deleteSet(Node *firstElem);

bool isUnderSet(Node* underSet, Node* set);

bool isEqualitySets(Node* firstElemA, Node* firstElemB);

Node* combiningTwoSets(Node* firstElemA, Node* firstElemB);

Node* intersectionTwoSets(Node* firstElemA, Node* firstElemB);

Node* differenceTwoSets(Node* firstElemA, Node* firstElemB);

Node* symmetricalDifferenceTwoSets(Node* firstElemA, Node* firstElemB);

int getRandomInt(int minValue, int maxValue);