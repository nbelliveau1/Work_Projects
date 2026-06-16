// =================== Support Code =================
// Doubly Linked List ( DLL ).
//
//
//
// - Implement each of the functions to create a working DLL.
// - Do not change any of the function declarations
//   - (i.e. dll_t* create_dll() should not have additional arguments)
// - You should not have any 'printf' statements in your DLL functions. 
//   - (You may consider using these printf statements to debug,
//     but they should be removed from your final version)
//   - (You may write helper functions to help you debug your code such as print_list etc)
// ==================================================
#ifndef MYDLL_H
#define MYDLL_H

// Create a node data structure to store data within
// our DLL. In our case, we will stores 'integers'
typedef struct node {
    void* data;
    struct node* next;
    struct node* previous;
} node_t;

// Create a DLL data structure
// Our DLL holds a pointer to the first node in our DLL called head,
// and a pointer to the last node in our DLL called tail.
typedef struct DLL {
    int count;              // count keeps track of how many items are in the DLL.
    node_t* head;           // head points to the first node in our DLL.
    node_t * tail;          //tail points to the last node in our DLL.
} dll_t;

// Creates a DLL
// Returns a pointer to a newly created DLL.
// The DLL should be initialized with data on the heap.
// (Think about what the means in terms of memory allocation)
// The DLLs fields should also be initialized to default values.
// Returns NULL if we could not allocate memory.
dll_t* create_dll(){
    //A data structure of a double linked list named newDLL is being allocated 
    //on the heap to the size of attributes within the dll_t data strucuture
    dll_t* myDLL = malloc(sizeof(dll_t));
        if (myDLL == NULL){return NULL;} //Returns null if the newDLL is currently NULL which indicates we failed to allocate memory for newDLL

    //Once memory allocated, now we intialize values for DLL
    myDLL->count = 0;
    myDLL->head = NULL;
    myDLL->tail = NULL;
    
    return myDLL;
}

// DLL Empty
// Check if the DLL is empty
// Exits if the DLL is NULL.
// Returns 1 if true (The DLL is completely empty)
// Returns 0 if false (the DLL has at least one element enqueued)
int dll_empty(dll_t* l){
    //Checks to see if the instance of a DLL exsits 
    if (l == NULL){
        exit(1);
    }
    //Checks to see if the head of the doubly linked list is empty; represented by NULL.
    //If so, it returns true represented by one
    if (l->head == NULL){
        return 1;
    //Otherwise, the instance of DLL has something in it
    //We return false represented by zero
    }else{
        return 0; 
    }
}

// push a new item to the front of the DLL ( before the first node in the list).
// Exits if DLL is NULL.
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// (i.e. the memory allocation for a new node failed).
int dll_push_front(dll_t* l, void* item){
	//Checks for the empty list 
    if(l == NULL){
		exit(1); //No DLL existing
	}

    //Allocates memory on the heap for newNode
	node_t* newNode = malloc(sizeof(node_t));

    ////Failed: Unable to allocate memory onto heap
	if (newNode == NULL){
		return 0; 
	}

	newNode ->data = item; //Assigns desired input from dll_push_front() to newNode

    //Condtion handling the instance of an empty list with no head node yet
	if (l->head == NULL){

		//Initialize struct feilds of node
		//Node pointers NULL d/t only node in list 
		newNode->next = NULL; 
		newNode->previous = NULL;

		//Position node at head and tail because there is only one node of list;
		l->head = newNode;
		l->tail = newNode;

		//Increments count by 1
		l->count++;
		return 1;

	}
	else{
	//Init newNode
	
	newNode->previous = NULL; //Pointer set to NULL because newNode first in list and cannot point to a prev node when first in list
	newNode->next = l->head; //Assigns the pointer to the current node at head position
	l->head->previous = newNode; //Links current node at head of list to newNode
	
	l->head = newNode; //THIS LINE SHIFTS ASSIGNS NEWNODE TO HEAD POSTION
	l->count++; //Increments count by one
	return 1;

	}
}
// push a new item to the end of the DLL (after the last node in the list).
// Exits if DLL is NULL.
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// (i.e. the memory allocation for a new node failed).
int dll_push_back(dll_t* l, void* item){
	
    //Checks if exsisting instance of DLL
    if(l == NULL){
		exit(1);
	}
	node_t* newNode = malloc(sizeof(node_t));
	if (newNode == NULL){
		return 0; //Failed: Unable to allocate memory onto the heap
	}

	newNode->data= item;

	if(l->head == NULL){
		//Init newNode
		//Initialize struct feilds of node
		//Node pointers NULL d/t only node in list 
		newNode->next = NULL;
		newNode->previous = NULL;

		//Both head and tail pointers assigned to point to newNode d/t only node within list 
		l->head = newNode;
		l->tail = newNode;

		l->count++;
		return 1;
	}
	else
        {
		newNode->next = NULL; //NewNode next point to nothing since its the last node
		newNode->previous = l->tail; //Links newNode to tail node
		l->tail->next = newNode; //Links current tailNode to newNode

		l->tail = newNode; //Assign tail pointer to point to newNode
		
		l->count++;
		return 1;
	} 
}

// Returns the first item in the DLL and also removes it from the list.
// Exits if the DLL is NULL. 
// Returns NULL on failure, i.e. there is noting to pop from the list.
// Assume no negative numbers in the list or the number zero.
void* dll_pop_front(dll_t* t){

    //Ensures instance of dll_t exsists 
	if (t == NULL){
		exit(1); //If t is unassigned, exits function
	}

    //Checks for an empty dll
    //If empty returns zero
	if (t->head == NULL){
		return NULL; //returns NULL because we are using *void as a return type and this is compatible with expected return of *void
	}


	/* NOTE TO SELF
	Save a pointer to the current head (the old front node).
 * Why this alias matters:
 *   1) Read its data before we change any pointers.
 *   2) Advance t->head to tempHead->next safely.
 *   3) Free the old head afterward to avoid a memory leak.
 * Important: If you did `t->head = t->head->next;` first, you’d lose the only
 * reference to the old head (leak). If you freed `t->head` first, you’d then
 * dereference freed memory (use-after-free). This is just a pointer alias—
 * no new allocation happens here.
 */

	node_t* tempHead = t->head; //Alais

	void* result = tempHead->data; //Stores value prior to deleting
	t->head = tempHead->next; //Advances head to next node in list

	if (t->head != NULL){
		t->head->previous = NULL; //New head has nothing to point to 
	}else{
		t->tail = NULL;
	}





	free(tempHead);
	t->count --;
	return result;
	
}
// Returns the last item in the DLL, and also removes it from the list.
// Exits if the DLL is NULL. 
// Returns NULL on failure, i.e. there is noting to pop from the list.
// Assume no negative numbers in the list or the number zero.
void* dll_pop_back(dll_t* t){
	
	if (t == NULL){
		exit(1);
	}

	if (t->tail == NULL){
		return NULL;
	}

	node_t* tempNode = t->tail; //Alais 
	void* result = tempNode ->data;
	t->tail = tempNode ->previous; //Tail being repostioned one node prior 

	//Conditional ensuring list is not empty
	if (t->tail != NULL){
		t->tail->next = NULL; ///Handles the next pointer for our newly adjusted t->tail
	}
	else{t->head = NULL;
		t->tail = NULL;}

	free(tempNode);
	t->count --;
	return result;

}

// Inserts a new node before the node at the specified position.
// Exits if the DLL is NULL
// Returns 1 on success
// Retruns 0 on failure:
//  * we couldn't allocate memory for the new node
//  * we tried to insert at a negative location.
//  * we tried to insert past the size of the list
//   (inserting at the size should be equivalent as calling push_back).
int dll_insert(dll_t* l, int pos, void* item){
	
	//Check for empty list 
	if (l == NULL){
		exit(1);
	}

	//Prevents us from inserting before the list
	if (pos<0){
		return 0;
	}
	//Prevents us from inserting past the list
	if (pos> l->count){
		return 0;
	}


	//Traverses through list 
	//Breaks while loop once we reach desired position
	int index =0;
	node_t* travNode = l->head;
	while(travNode !=NULL && index<pos){
		travNode = travNode->next;
		index++;
	}
		
	//Allocate size for newNode
	node_t* newNode = malloc(sizeof(node_t));
	if (!newNode){return 0;}

	newNode->data = item;

	//For adding a new node to an empty list 
	if (l->count == 0){
		newNode->previous =NULL; //Nothing to point to
		newNode ->next = NULL;
		//Sets position of head and tail pointers of list 
		l->head = newNode;
		l->tail = newNode;
		//Updates list count
		l->count++;
		return 1;
	}

	//For inserting at end of list 
	if (travNode==NULL && pos==l->count){
		newNode->next = NULL; //New Node doesnt point to anything because its the last in the list 
		newNode->previous = l->tail; //Links newNode to the current tail node
		l->tail->next = newNode; //Links the old tail node to the newNode
		l->tail = newNode; //Updates pointer of tail to newNode
		l->count++;
		return 1;
	}

	

	//1)Assigns pointer positions for newNode
	newNode->previous = travNode->previous; //newNode goes before travNode
	newNode->next = travNode;       //newNode next is the current position of travNode

	//2)Stiches left node to newNode
	//Checks if there is a prev position
	//If travNode->prev ==NULL, that means we are at the head of the list 
	//The else condition places the newNode at the head
	if (travNode->previous){
		travNode ->previous ->next =newNode;
	}else{
		l->head = newNode; //For Node insertion where intended to insert at beginning of list
	}

	//3)Stich right node
	travNode->previous = newNode;

	l->count++;
	return 1;


	//return -1; // Note: This line is a 'filler' so the code compiles.
}

// Returns the item at position pos starting at 0 ( 0 being the first item )
// Exits if the DLL is NULL
// Returns NULL on failure:
//  * we tried to get at a negative location.
//  * we tried to get past the size of the list
// Assume no negative numbers in the list or the number zero.
void* dll_get(dll_t* l, int pos){
	//Checks 
	if (l==NULL){exit(1);}//Fails if list is empty 
	if(pos<0){return NULL;} //Fails if query is below 0
	if (pos>=l->count){return NULL;} //Fails if query is pos is greater than elements in list

	node_t* travNode = l->head; //Positioning node so it can traverse through list 
	for(int i = 0; i <pos; i++){
		travNode = travNode->next;
	}
    void* result = travNode->data;
	return result;
	
	//return -1; // Note: This line is a 'filler' so the code compiles.
}

// Return the zero-based index of target in the list, or -1 if not found.
int dll_index_of(dll_t *l, void *target) {
    if (!l || !l->head) return -1;
    int i = 0;
    for (node_t *p = l->head; p; p = p->next, ++i) {
        if (p->data == target) return i;   // pointer comparison
    }
    return -1;
}


// Removes the item at position pos starting at 0 ( 0 being the first item )
// Exits if the DLL is NULL
// Returns NULL on failure:
//  * we tried to remove at a negative location.
//  * we tried to remove get past the size of the list
// Assume no negative numbers in the list or the number zero.
void* dll_remove(dll_t* l, int pos){
	//Checks 
	if (l==NULL){exit(1);}//Fails if list is empty 
	if(pos<0){return NULL;} //Fails if query is below 0
	if (pos>=l->count){return NULL;} //Fails if query is pos is greater than elements in list

	//Traverses from head node to desired position
	node_t* travNode = l->head;
	for (int i = 0; i < pos; i ++){
		travNode = travNode->next;
	}

	void* removed = travNode->data;
	
	//Links node left of travNode
	if (travNode->previous != NULL){
		travNode->previous->next = travNode->next;
		//Removing from head
	}else l->head = travNode->next;

	//Links node right of travNode
	if (travNode->next !=NULL){
		travNode->next->previous = travNode->previous;
		 //Removing from tail
	}else l->tail = travNode->previous;

	free(travNode);
	l->count--;

	return removed;
	

}

int dll_size(dll_t* t){
	if(t == NULL) return -1;
	return t->count;
	//return -1; // Note: This line is a 'filler' so the code compiles.
}

// Free DLL
// Exits if the DLL is NULL.
// Removes a DLL and all of its elements from memory.
// This should be called before the proram terminates.
void free_dll(dll_t* t){
    // TODO: Implement me!!    
}

#endif
