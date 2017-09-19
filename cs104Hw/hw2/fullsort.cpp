// Example program
#include <list>
#include <iostream>
#include <string>
using namespace std;

struct Node {
	int value;
	Node *next;
};

Node* helperSort(Node * head, Node * current, Node* lastNode);

Node* findNode(Node* headCurrent );

Node* fullsort(Node * head) {

	Node* current = head;
	Node* headCurrent =  head;
	Node* lastNode = head;

	lastNode = findNode(headCurrent);

	head = helperSort(head,current,lastNode);


	return head;
}     

Node* findNode(Node* headCurrent) {
	if (headCurrent -> next != nullptr) {
		headCurrent = headCurrent -> next;
		return findNode(headCurrent);	
	}
	else {
		return headCurrent;
	}
}


Node*  helperSort(Node * head, Node * current, Node* lastNode) {
	if (current ->next == nullptr) {
		return head;
	}

	if (current -> value <= (current->next) -> value) {
		current = current->next; //advance current by one, if the array is sorted, it will return first value.
		return helperSort(head,current,lastNode);
	}

	else if (current -> value > (current->next) -> value) {
		lastNode -> next = head;
		head = (current -> next);
		current-> next = nullptr;		
		return head;
	}
	return head;
}
