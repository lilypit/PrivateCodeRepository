## HW 2 

## CS104 Assignment by Jacob Pitts

Permutations.cpp: 
	
	Works by passing a string into the function. The output should print all permutations to the console.

Fullsort.cpp:
	
	Works by passing the head pointer to mostly sorted linked list of Nodes into the function. 
	The function should return a pointer to the first element of the sorted
	linked list. 

Company.cpp:
	
	Works by creating a company by using the CompanyTracker struct. Companies can then be merged and split. 
	The merged and split functions should not do anything for values out of bounds (ie > numcompanies or <0).

	I am aware that the function could have been deallocated by splitting. I chose to use a 
	vector to deallocate companies - this should be an acceptable way to deallocate.

Note:
	
	All functions should be compiled with c++11. If not compiled with c++11 in mind,
	nullptr, used in both company.cpp & fullsort.cpp will not function correctly. 

___

### Example main functions have been listed below. 
### Main functions have been omitted from all .cpp files per instruction.  
___


Permutations.cpp: 
	
```cpp
int main() {
  	permutations("12345678910"); 
}
```

Fullsort.cpp:

```cpp
int main() {

	int array[5] = {2,2,2,2,2};

	Node* one = new Node;
	Node* two = new Node;
	Node* three = new Node;
	Node* four = new Node;
	Node* five = new Node; 
	Node* headVal; 
	five -> next = NULL; 
	five -> value = array[4];
	four -> next = five; 
	four -> value = array[3];
	three -> next = four; 
	three -> value = array[2];
	two -> next = three; 
	two -> value = array[1];
	one -> next = two; 
	one -> value = array[0];
	headVal = one; 

	headVal = (fullsort(one)); //head pointer, iterate through to find connected list

	cout << headVal -> value;
	cout << headVal -> next -> value;
	cout << headVal -> next -> next -> value;
	cout << headVal -> next -> next -> next -> value;
	cout << headVal -> next -> next -> next -> next -> value << endl;


	delete one;
	delete two;
	delete three;
	delete four;
	delete five;

}

```



Company.cpp:

```cpp
int main() {
  CompanyTracker merger(5); //creating object merger
  merger.merge(0,1);
  merger.merge(0,2); 
  merger.merge(1,2);
}
```