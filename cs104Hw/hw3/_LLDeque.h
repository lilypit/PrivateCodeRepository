struct Node {
  // your standard node class, containing a character as data
  
  Node *next, *prev;
  char data;

  Node (char d, Node *n, Node *p)
  { data = d; next = n; prev = p; }

  Node (char d)
  { data = d; next = nullptr; prev = nullptr; }
};


class LLDeque {
  // Implements a deque by using a doubly linked list underneath
  
 public:
   LLDeque (); // initializes an empty deque

  ~LLDeque (); // deallocates all dynamically allocated memory

  void pushback (char x); // append x at one end of the deque.

  void popback (); /* remove at the same end of the deque.
                     Does nothing if called on an empty deque. */

  char getback (); /* returns the element at the same end of the deque.
                      Returns '\0' if called on an empty deque. */

  void pushfront (char x); // "prepend" x at the other end of the queue.

  void popfront (); /* remove at the other end of the deque.
                       Does nothing if called on an empty deque. */

  char getfront(); /* returns the element at the other end of the deque.
                      Returns `\0` if called on an empty deque. */

  bool isempty(); // returns whether the deque is empty.

 private:
  // Feel free to add private helper functions and data members as you see fit.

  Node* head;
  Node* tail;

};