//g++ -g -std=c++11 -Wall _LLDeque.cpp -o _LLDeque
//valgrind --tool=memcheck --leak-check=yes --suppressions=/home/student/gcc.supp ./_LLDeque

#include "_LLDeque.h"
#include <iostream>
using namespace std;

LLDeque::LLDeque() {
	head = nullptr;
	tail = nullptr;
}

LLDeque::~LLDeque() {
	while (head != nullptr) {
		Node* tempHead = head;
		head = head-> next;
		delete tempHead;
	}
}

bool LLDeque::isempty() {
	return ((head == nullptr) && (tail == nullptr));
}

void LLDeque::pushback(char x) {
	if (isempty() == false) {
		Node* newTail = new Node(x,nullptr,tail);
		tail-> next = newTail;
		tail = newTail;
	}
	else {
		pushfront(x); 
	}
}

void LLDeque::popback () {  
	if (isempty() == false) {
		if (tail-> prev == nullptr) {
			tail = nullptr;
			head = nullptr;
		}
		else {
		Node* tempTail = tail;
		tail = tail->prev;
		tail-> next = nullptr;
		delete tempTail;
	}
	}
	return;
}
char LLDeque::getback (){  
	if (isempty() == false) {
		return tail-> data;
	}
	return '\0';
}

void LLDeque::pushfront (char x) { 
	Node* newHead = new Node(x,head,nullptr);
	if (isempty() == false) {
		head->prev = newHead;
		head = newHead;
	}
	else {
		head = newHead;
		tail = newHead;
	}
	return;
}


void LLDeque::popfront () {
	if (isempty() == false) {
		if (head-> next == nullptr) {
			tail = nullptr;
			head = nullptr;
		}
		else {
		Node* tempHead = head;
		head = head->next;
		head-> prev = nullptr;
		delete tempHead;
	}
	}
	return;
}


char LLDeque::getfront() {  
	if (isempty() == false) {
		return head-> data;
	}
	return '\0';
}
