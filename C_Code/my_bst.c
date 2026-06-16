// Nicholas Belliveau
// November 6rd, 2025

//
// Include our header file for our my_bst.c
#include "my_bst.h"

// Include any other libraries needed
#include <stdio.h>
#include <stdlib.h>

bstnode_t* node_Create(int data){
    //Allocate memory for new node 
    bstnode_t* newNode = malloc(sizeof(bstnode_t));
    if (!newNode) return NULL;

    //Initialize the beginning parameters of a new node 
    newNode->data = data;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;

    return newNode;


}

// Creates a BST "Think initialize values of structures"
// Returns a pointer to a newly created BST.
// The BST should be initialized with data on the heap.
// The BST fields should also be initialized to default values(i.e. size=0).
bst_t* bst_create(){
    
    bst_t* newBST = malloc(sizeof(bst_t)); //Allocates memory
    
    if (newBST == NULL) {
        return NULL; //Malloc failed; error prevention
    }

    newBST->root = NULL; //Inits BST as empty 
    newBST ->size = 0;

    return newBST;
}

// BST Empty
// Check if the BST is empty
// Returns 1 if true (The BST is completely empty)
// Returns 0 if false (the BST has at least one element)
int bst_empty(bst_t* t){

    if (t == NULL){
        exit(1); //Protects against an uninit BST
    }

    if (t->size == 0){
        return 1; //Returns true; BST with 0 elements within tree
    }

    return 0;
}

//Helper function for bst_add()
//Recursively traverses through nodes within the tree structure until a NULL position is found
//params: Instance of a BSTNode, int value for node 

// Helper function for bst_add()
// Recursively traverses through nodes until a NULL position is found
// Params: pointer to a BST node, int value for node
int bst_add_helper(bstnode_t* root, int data) {

    // Go left
    if (data <= root->data) {

        if (root->leftChild == NULL) {
            bstnode_t* newNode = node_Create(data);
            if (!newNode) return -1;        // malloc failed
            root->leftChild = newNode;
            return 1;
        }

        return bst_add_helper(root->leftChild, data);
    }

    // Otherwise, go right
    else {

        if (root->rightChild == NULL) {
            bstnode_t* newNode = node_Create(data);
            if (!newNode) return -1;
            root->rightChild = newNode;
            return 1;
        }

        return bst_add_helper(root->rightChild, data);
    }
}




// Adds a new node containg item to the BST
// The item is added in the correct position in the BST.
//  - If the data is less than or equal to the current node we traverse left
//  - otherwise we traverse right.
// The bst_function returns '1' upon success
//  - bst_add should increment the 'size' of our BST.
// Returns a -1 if the operation fails.
//      (i.e. the memory allocation for a new node failed).
// Your implementation should should run in O(log(n)) time.
//  - A recursive imlementation is suggested.
int bst_add(bst_t* t, int item){
    //Checks for uninited BST
    if (t == NULL){
        return -1;
    }

    //If the root is empty, assigns node as root
    if (t->root == NULL){
        bstnode_t* newNode = node_Create(item);
            if(!newNode) return -1;
        t->root = newNode;
        t->size ++;
        return 1;
    }
    //Otherwise recursively insert into the substree
    int result = bst_add_helper(t->root, item);
    if (result == 1){
        t->size ++;// Increments only if a new node has been inserted
    }
    return result;



}

void print_helper(bstnode_t* node, int order){
    if (node == NULL)return;
    
    //Prints ascending order 
    if(order == 0){
    print_helper(node->leftChild, order); //Recursive call to the left subtree
    printf("%d", node->data); //Visit current node
    print_helper(node->rightChild, order); //Recursive call to right subtree
    }
    else{
    print_helper(node->rightChild, order); //Recursive call to the right subtree
    printf("%d", node->data); //Visit current node
    print_helper(node->leftChild, order); //Recursive call to left subtree
    }
}

// Prints the tree in ascending order if order = 0, otherwise prints in descending order.
// A BST that is NULL should print "(NULL)"
// It should run in O(n) time.
void bst_print(bst_t *t, int order){
    if(NULL == t || t->root == NULL){
        printf("(NULL)");
        return;
    }
    else print_helper(t->root, order);

   
}
// Returns the sum of all the nodes in the bst. 
// A BST that is NULL exits the program.
// It should run in O(n) time.
int bst_sum(bst_t *t){
    if (t==NULL) exit(1);

    if (t->root == NULL){
        return 0;
    }

    int sum = 0; 
    bstnode_t* stack[t->size];
    int top = -1;
    bstnode_t* current = t->root;

    while (current != NULL || top >=0){
        //go to left
        while (current != NULL){
            stack[++top] = current; //Adding the node onto the stack until we reach a node that has NULL leftchild
            current = current->leftChild; //Update the next node to be placed onto the stack 
        }
        //Visits node
        current = stack[top--];
        sum += current->data;

        current = current ->rightChild;
    }

    
    return sum;
}

// Returns 1 if value is found in the tree, 0 otherwise. 
// For NULL tree -- exit the program. 
// It should run in O(log(n)) time.
int bst_find(bst_t * t, int value){

    if (t == NULL) {exit(1);}

    //Needs local pointer so we are mutating root
    //We want to mutate local pointer instead

    bstnode_t* traverseNode = t->root;


    while (traverseNode != NULL){

        if (value == traverseNode->data){
            return 1;
    }
        if (traverseNode->data > value){
            traverseNode = traverseNode->leftChild;
        }
        else if(traverseNode->data< value){
            traverseNode = traverseNode ->rightChild;
        }
    }return 0;
}


// Returns the size of the BST
// A BST that is NULL exits the program.
// (i.e. A NULL BST cannot return the size)
unsigned int bst_size(bst_t* t){
    if (t == NULL){exit(1);}

    int sizeOfTree = t->size;

    return sizeOfTree;
}


//Helper function to free nodes recursively
void bst_free_helper(bstnode_t* n){
    //Base case 
    if (n == NULL){
        return;
    }
    else { 
         bst_free_helper(n->leftChild);
         bst_free_helper(n->rightChild);
         free(n);}
}

// Free BST
// Removes a BST and ALL of its elements from memory.
// This should be called before the proram terminates.
void bst_free(bst_t* t){
    if (t == NULL) {return;} //Tree has been completely freed
    bst_free_helper(t->root); //Recurseively frees left and right side 
    free(t); //Frees bst structure

}



