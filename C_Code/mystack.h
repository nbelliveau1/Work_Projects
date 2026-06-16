// =================== Support Code =================
// Stack
//
//
//
// - Implement each of the functions to create a working stack.
// - Do not change any of the function declarations
//   - (i.e. stack_t* create_stack() should not have additional arguments)
// - You should not have any 'printf' statements in your stack functions. 
//   - (You may consider using these printf statements to debug, 
//      but they should be removed from your final version)
// ==================================================
#ifndef MYSTACK_H
#define MYSTACK_H

// Stores the maximum 'depth' of our stack.
// Our implementation enforces a maximum depth of our stack.
// (i.e. capacity cannot exceed MAX_DEPTH for any stack)
# define MAX_DEPTH 32

// Create a node data structure to store data within
// our stack. In our case, we will stores 'integers'
typedef struct node{
	int data;         //Holds an int value
	struct node* next;//Points to a new instance of a struct node via memory address
}node_t;

// Create a stack data structure
// Our stack holds a single pointer to a node, which
// is a linked list of nodes.
typedef struct stack{
	int count;		// count keeps track of how many items
				// are in the stack.
	unsigned int capacity;	// Stores the maximum size of our stack
	node_t* head;		// head points to a node on the top of our stack.

}stack; //Had to change "stack_t" to "stack" due crashing program at runtime on mac!"
		//Mistaking stack_t as a different stuct type on mac machine

// Creates a stack
// Returns a pointer to a newly created stack.
// The stack should be initialized with data on the heap.
// (Think about what the means in terms of memory allocation)
// The stacks fields should also be initialized to default values.
stack* create_stack(unsigned int capacity){
	//If statement to ensure we dont go over the stack limit of 32
	if (capacity > MAX_DEPTH){
		capacity = MAX_DEPTH;
	}

	stack* myStack = malloc(sizeof(stack));//Allocating memory for myStack on the heap
	myStack->capacity = capacity; //Sets the total capacity of our stack up to 32 elements 
	myStack->count = 0; // number of elements 
	myStack ->head = NULL; //Marks the head position to be empty

	return myStack;
}

// Stack Empty
// Check if the stack is empty
// Returns 1 if true (The stack is completely empty)
// Returns 0 if false (the stack has at least one element enqueued)
int stack_empty(stack* s){
	if (s->count == 0){
		return 1; //True, stack is empty 
	}

	return 0; //Stack has something inthe element 
}

// Stack Full
// Check if the stack is full
// Returns 1 if true (The Stack is completely full, i.e. equal to capacity)
// Returns 0 if false (the Stack has more space available to enqueue items)
int stack_full(stack* s){
	if (s == NULL){
		return 0; //No stack present 
	}
	if (s->count == s->capacity){
		return 1; //Stack if full
	}

	return 0; //Stack is not full
}

// Enqueue a new item
// i.e. push a new item into our data structure
// Returns a -1 if the operation fails (otherwise returns 0 on success).
// (i.e. if the Stack is full that is an error, but does not crash the program).
int stack_enqueue(stack* s, int item){

	if (s->count == s->capacity){
		return -1; //Returns false because stack is full. 
	}

	node_t* newNode =malloc(sizeof(node_t));  //Allocate memory on heap for new node
	newNode->data =item; //Setting the IOS (instance of struct) to the enque int item
	newNode ->next = s->head; //links the new node to the old stack.
	s->head = newNode; //HEAD NODE POINTS TO NEWNODE!
	s->count++; 

	return 0;

}

// Dequeue an item
// Returns the item at the front of the stack and
// removes an item from the stack.
// Removing from an empty stack should crash the program, call exit(1).
int stack_dequeue(stack* s){
	if (s== NULL || s->head == NULL){
		exit(1); //Completely exits the program
	}
	
	node_t* tempNode = s->head; //Create a temporary node to access head
	int results = tempNode->data; //Results assigned to value at head of stack
	s->head = tempNode->next; //Sets the head to the next node within the stack 
	free(tempNode);          //Removes temp node from the heap

	s->count--;             //Decreases count of stack by one

	return results;

	//return 9999999; // Note: This line is a 'filler' so the code compiles.
}

// Stack Size
// Queries the current size of a stack
// A stack that has not been previously created will crash the program.
// (i.e. A NULL stack cannot return the size)
unsigned int stack_size(stack* s){
	if (s == NULL){
		exit(1); //Completely exits the program
	}

	return s->count; //Returns current count of the stack
}

// Free stack
// Removes a stack and ALL of its elements from memory.
// This should be called before the proram terminates.
void free_stack(stack* s){
	if (s == NULL){
		return;
	}
	node_t* headNode = s->head;
	while (headNode != NULL){

		/*
		We store that “next node pointer” in a temporary variable (nextNode).
		This way even if we free(headNode) we still have the address of the rest of the list so we can keep traversing.
		*/
		node_t* nextNode = headNode -> next;
		free(headNode);
		headNode = nextNode;
	}
	free(s);
	
}

#endif
