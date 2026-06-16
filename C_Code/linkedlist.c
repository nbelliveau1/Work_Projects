// Modify this file
// compile with: gcc linkedlist.c -o linkedlist
// Nicholas  Belliveau
// TODO: 10/1/2025
// Lab02 CS5008 FAll 2025

#include <stdio.h>
#include <stdlib.h> // contains the functions free/malloc

// TODO: Create your node_t type here
typedef struct node{
	int value; //Holds value 
	int value2;
	struct node* next; //Next is a placeholder for the next node, if created
}node_t;

// TODO: Write your functions here
// There should be 1.) create_list 2.) print_list 3.) free_list
// You may create as many helper functions as you like.

//Step 2: Created a function that creates a list of linked list:

//Function: Create Node
//Initializes potential instance of node
node_t* createNode(int numOfWins, int yearOfWin){
	node_t* newNode = malloc(sizeof(node_t)); //Allocating memory for new node 

	if (newNode == NULL){
		exit(1);
	}
	
	newNode ->value = numOfWins; //Assigns number of wins to node
	newNode ->value2 = yearOfWin;
	newNode ->next = NULL; // Initialize pointer to next node as NULL

	return newNode;
}

node_t* createList(int wins[],int years[], int size){
	if (size == 0) return NULL;
	node_t* headNode = createNode(wins[0],years[0]); //Creation of head node; head node assigned value from position zero of wins array

	/*
		Notes to self:
		
		Current and head both point to the same node in memory:
		HeadNode is used to identify the starting point of the list
		CurrentNode shares same memory address of headNode, then walks down the link to link new ones 
	*/
	node_t* currentNode = headNode;

	for (int i = 1; i < size; i++){ //REVIEW

		//At beginning of for loop, currentNode is sharing memory address as headNode
		//Below, currentNode points to the newly created node within the for loop
		//This is at the heart of linking the nodes together
		currentNode ->next = createNode(wins[i],years[i]);
		currentNode = currentNode->next;
	}
	return headNode; 
}

void printList (node_t* node){
	while (node != NULL){
		printf("%d, %d wins\n",node->value2, node->value);
		node = node->next;
	}}

void free_list(node_t*node){
	if (node == NULL){
		return;//Nothing to clear
	}
	while (node != NULL){
			node_t* nextNode = node->next; //Where to go next
			free(node);				  //Frees current node
			node = nextNode;	      //Takes node and points it to next node
			
		}
	}



int main(){
	
	//Step 3: Create a loop that enters wins into create node method 
	int wins[] = {71, 78, 93, 93, 108};
	int year[] = {2014,2015,2016,2017,2018};
    int size = sizeof(wins) / sizeof(wins[0]);

    node_t* head = createList(wins,year, size);

    printList(head);
	free_list(head);

	return 0;
}
