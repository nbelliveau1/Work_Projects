// =================== Support Code =================
// Graph.
//
// - Implement each of the functions to create a working graph.
// - Do not change any of the function declarations
//   - (i.e. graph_t* create_graph() should not have additional arguments)
// - You should not have any 'printf' statements in your graph functions.
//   - (You may consider using these printf statements to debug, but they 
//      should be removed from your final version)
// ==================================================
#ifndef MYGRAPH_H
#define MYGRAPH_H

#include "my_dll.h"
#include <stdlib.h>
#include <assert.h>
// Create a graph data structure
typedef struct graph{
    int numNodes;
    int numEdges;
    dll_t* nodes;     //an array of nodes storing all of our nodes.
} graph_t;

typedef struct graph_node{
    int data;
    dll_t* inNeighbors;
    dll_t* outNeighbors;
} graph_node_t;

// Creates a graph
// Returns a pointer to a newly created graph.
// The graph should be initialized with data on the heap.
// The graph fields should also be initialized to default values.
// Returns NULL if we cannot allocate memory.
graph_t* create_graph(){
    // Modify the body of this function as needed.
    graph_t* myGraph= malloc(sizeof(graph_t));
    myGraph->nodes = create_dll();
    myGraph->numEdges = 0;
    myGraph->numNodes = 0;
    return myGraph;
}
//NOTES TO SELF
/*
When we initialize the while loop, we use the node_t* type because we’re traversing the doubly linked list itself — that’s the container structure that holds our graph nodes.
Each node in that doubly linked list (node_t) has a void* data field that stores a pointer to a graph_node_t.
Inside the while loop, we cast that generic void* payload to a graph_node_t*, so that we can access its fields (like data or neighbors).
If we find a graph node whose data matches the target value, we return that graph_node_t* — confirming that the node exists in the graph
*/
// Returns the node pointer if the node exists.
// Returns NULL if the node doesn't exist or the graph is NULL
graph_node_t* find_node( graph_t * g, int value){
    
    //Ensures instance of graph has been created 
    if(g == NULL){
        exit(1);
    }
    node_t* travNode = g->nodes->head;
    while(travNode!=NULL){
     graph_node_t* current = (graph_node_t*) travNode->data;
     if (current->data == value){
        return current;
     }else travNode = travNode->next;

    }return NULL;
}

// Creates a graph node
// Note: This relies on your dll implementation.
graph_node_t * create_graph_node(int value){
    graph_node_t * graph_node = malloc(sizeof(graph_node_t));
    
    if ( graph_node == NULL ) return NULL;
    
    graph_node->data = value;
    graph_node->inNeighbors = create_dll();
    graph_node->outNeighbors = create_dll();
    
    return graph_node;
}

// Returns 1 on success
// Returns 0 on failure ( or if the node already exists )
// Returns -1 if the graph is NULL.
int graph_add_node(graph_t* g, int value){
    if ( g == NULL ) return -1;
    
    if (find_node(g, value) != NULL) return -1;
    
    graph_node_t * newNode = create_graph_node(value);
    if ( newNode == NULL ) return -1;
    
    assert(g->nodes);
    dll_push_back(g->nodes, newNode);
    g->numNodes++;
    
    return 1;
}

// Returns 1 on success
// Returns 0 on failure ( or if the node doesn't exist )
// Returns -1 if the graph is NULL.
int graph_remove_node(graph_t* g, int value){

    if (g == NULL){
        return -1;
    }

     //First condition is handling the empty graph
    if (g->nodes == NULL || g->nodes->head == NULL){
        return 0;
    }
    //Creating a gernric node to traverse DLL
    node_t* travNode = g->nodes->head;


    //Second condition is locating the desired node we would like to remove from the list and returning success
    while(travNode !=NULL){
        //Create a graphNode to access data 
        graph_node_t* currentNode = (graph_node_t*)travNode ->data; //Maintain position of travNode but specifically looking at the data within DLL
        if (currentNode && currentNode->data == value){
            //We need to unlink the travNode pointer from DLL to prevent dangling pointer within array
            if (travNode->previous){
                //Take the previous node and set its next pointer to the node to the right of the one we are removing
                travNode->previous->next = travNode->next;}
                else g->nodes->head = travNode->next;
            if (travNode->next){
                travNode->next->previous = travNode->previous;}
                else {g->nodes->tail = travNode->previous;}

            g->numNodes--;
            free(travNode);
            free(currentNode);
            return 1;
            }
            
        
        }
    return 0;
}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge already exists )
// Returns -1 if the graph is NULL.
    // TODO: Implement me!
    // The function adds an edge from source to destination but not the other way.
    // Make sure you are not adding the same edge multiple times.
    // Make sure you modify the in and out neighbors appropriatelly. destination will be an out neighbor of source.
    // Source will be an in neighbor of destination.
int graph_add_edge(graph_t * g, int source, int destination){
    
    //Check if graph has been init
    if (g == NULL){
        return -1;
    }

    //Checks for empty list which we have no means of adding an edge
    if (g->nodes == NULL || g->nodes->head == NULL){
        return 0;
    }
    //Two graph nodes to hold memory location of source and destination if found within for loop
    graph_node_t* src =NULL, *dst = NULL;

    //For loop that has DLL pointer traversing through DLL list 
    for(node_t* travNode = g->nodes->head; travNode != NULL && (!src || !dst) ; travNode = travNode->next){
        if (!travNode->data) continue;
        //Graph node needed to acccess data within DLL
        graph_node_t* graphTravNode = (graph_node_t *) travNode->data;
        if(graphTravNode->data == source){
            src = graphTravNode;
        }
        else if (graphTravNode->data == destination){
            dst = graphTravNode;
        }
    }
    //validating both nodes are here 
    //Fails program
    if (!src || !dst) return 0;
    if (!src->outNeighbors || !dst->inNeighbors) return 0; // lists must exist

     // Prevent duplicates: is dst already in src->outNeighbors?
    for (node_t *e = src->outNeighbors->head; e != NULL; e = e->next) {
        if ((graph_node_t *)e->data == dst) return 0; // edge exists
    }
    
    // Insert into out(src) and in(dst). Update count only if both succeed.
    if (!dll_push_back(src->outNeighbors, dst)) return 0;
    if (!dll_push_back(dst->inNeighbors,  src)) {
        return 0;
    }
    g->numEdges++;
    return 1;

}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge doesn't exists )
// Returns -1 if the graph is NULL.
int graph_remove_edge(graph_t * g, int source, int destination){
    
    //Check if graph has been init
    if (g == NULL){
        return -1;
    }

    //Checks for empty list which we have no means of adding an edge
    if (g->nodes == NULL || g->nodes->head == NULL){
        return 0;
    }
    //Two graph nodes to hold memory location of source and destination if found within for loop
    graph_node_t* src =NULL, *dst = NULL;

    //For loop that has DLL pointer traversing through DLL list 
    for(node_t* travNode = g->nodes->head; travNode != NULL && (!src || !dst) ; travNode = travNode->next){
        if (!travNode->data) continue;
        //Graph node needed to acccess data within DLL
        graph_node_t* graphTravNode = (graph_node_t *) travNode->data;
        if(graphTravNode->data == source){
            src = graphTravNode;
        }
        else if (graphTravNode->data == destination){
            dst = graphTravNode;
        }
    }
    //validating both nodes are here 
    //Fails program
    if (!src || !dst) return 0;
    if (!src->outNeighbors || !dst->inNeighbors) return 0; // lists must exist


    //Given arrangement of dll_Remove we need to find the index of our source and destination node
    int index_out =dll_index_of(src->outNeighbors, dst);
    int index_in = dll_index_of(dst->inNeighbors, src);
    if (index_out< 0 || index_in<0) return 0;

    void * removed_out = dll_remove(src->outNeighbors, index_out);
    if (removed_out != (void *)dst) return 0;

    void *removed_in = dll_remove(dst->inNeighbors, index_in);
    if(removed_in != (void *)src) return 0;

    g->numEdges --;
    return 1;


}

// Returns 1 on success (edge source -> destination exists)
// Returns 0 on failure (or if the source or destination nodes don't exist)
// Returns -1 if the graph is NULL.
int contains_edge(graph_t *g, int source, int destintaion) { // NOTE: 'destintaion' is misspelled; kept as-is
    // Guard: invalid graph pointer
    if (g == NULL) {
        return -1;
    }

    // Guard: graph has no nodes
    if (g->nodes == NULL || g->nodes->head == NULL) {
        return 0;
    }

    // Pointers to hold the source and destination graph nodes (once found)
    graph_node_t *src = NULL, *dst = NULL;

    // Traverse the DLL of all graph nodes to locate the node with value 'source'
    // and the node with value 'destintaion'. Stop early once both are found.
    for (node_t *travNode = g->nodes->head; travNode && (!src || !dst); travNode = travNode->next) {
        if (!travNode->data) continue; // Defensive: skip if node payload is NULL

        graph_node_t *travGraphNode = (graph_node_t *)travNode->data;

        // Match source by value
        if (travGraphNode->data == source) {
            src = travGraphNode;
        }
        // Match destination by value (parameter name is 'destintaion')
        else if (travGraphNode->data == destintaion) {
            dst = travGraphNode;
        }
    }

    // If either endpoint wasn't found, the edge cannot exist
    if (!src || !dst) {
        return 0;
    }

    // If the source has no out-neighbor list (or it's empty), no outgoing edges to check
    if (!src->outNeighbors || !src->outNeighbors->head) {
        return 0;
    }

    // Scan the source's out-neighbor DLL.
    // Each DLL node's 'data' holds a (graph_node_t*) to a neighbor.
    // We check for exact pointer identity with 'dst'.
    for (node_t *e = src->outNeighbors->head; e; e = e->next) {
        if ((graph_node_t *)e->data == dst) {
            // Found 'dst' within 'src' out-neighbors: edge (source -> destination) exists
            return 1;
        }
    }

    // If we finish the scan without finding 'dst', the edge doesn't exist
    return 0;
}


// Returns dll_t* of all the in neighbors of this node.
// Returns NULL if thte node doesn't exist or if the graph is NULL.
dll_t* getInNeighbors( graph_t * g, int value ){
    //Guard agaist empty G
    if(g == NULL){
        return NULL;
    }
    //If graph is empty
    if (g->nodes == NULL || g->nodes->head == NULL){
        return NULL;
    }
    graph_node_t* StartingInNeighborNode = NULL;
    //For loop traverses through DLL looking for DLL with matching value
    for(node_t* travNode = g->nodes->head; travNode ; travNode = travNode->next){
        if(!travNode->data) continue;
        graph_node_t* graphTravNode = travNode->data;

        //If the graphNode matches the value then we update the global graph node within the function
        if(graphTravNode->data == value){
            StartingInNeighborNode = graphTravNode;
            return StartingInNeighborNode->inNeighbors;
        }
    }return NULL;
}

// Returns the number of in neighbors of this node.
// Returns -1 if the graph is NULL or the node doesn't exist.
int getNumInNeighbors( graph_t * g, int value){
    //Guard agaist empty G
    if(g == NULL){
        return -1;
    }
    //If graph is empty
    if (g->nodes == NULL || g->nodes->head == NULL){
        return -1;
    }
    graph_node_t* StartingInNeighborNode = NULL;
    //For loop traverses through DLL looking for DLL with matching value
    for(node_t* travNode = g->nodes->head; travNode ; travNode = travNode->next){
        if(!travNode->data) continue;
        graph_node_t* graphTravNode = travNode->data;

        //If the graphNode matches the value then we update the global graph node within the function
        if(graphTravNode->data == value){
            StartingInNeighborNode = graphTravNode;
            //If StartingINNeighborNode is not null return the count; otherwise return 0
            return (StartingInNeighborNode->inNeighbors ? StartingInNeighborNode->inNeighbors->count: 0);
        }
    }return -1;

}

// Returns dll_t* of all the out neighbors of this node.
// Returns NULL if thte node doesn't exist or if the graph is NULL.
dll_t* getOutNeighbors( graph_t * g, int value ){
    //Guard agaist empty G
    if(g == NULL){
        return NULL;
    }
    //If graph is empty
    if (g->nodes == NULL || g->nodes->head == NULL){
        return NULL;
    }
    graph_node_t* StartingOutNeighborNode = NULL;
    //For loop traverses through DLL looking for DLL with matching value
    for(node_t* travNode = g->nodes->head; travNode ; travNode = travNode->next){
        if(!travNode->data) continue;
        graph_node_t* graphTravNode = travNode->data;

        //If the graphNode matches the value then we update the global graph node within the function
        if(graphTravNode->data == value){
            StartingOutNeighborNode = graphTravNode;
            return StartingOutNeighborNode->outNeighbors;
        }
    }return NULL;

}

// Returns the number of out neighbors of this node.
// Returns -1 if the graph is NULL or the node doesn't exist.
int getNumOutNeighbors( graph_t * g, int value){
    //Guard agaist empty G
    if(g == NULL){
        return -1;
    }
    //If graph is empty
    if (g->nodes == NULL || g->nodes->head == NULL){
        return -1;
    }
    graph_node_t* StartingOutNeighborNode = NULL;
    //For loop traverses through DLL looking for DLL with matching value
    for(node_t* travNode = g->nodes->head; travNode ; travNode = travNode->next){
        if(!travNode->data) continue;
        graph_node_t* graphTravNode = travNode->data;

        //If the graphNode matches the value then we update the global graph node within the function
        if(graphTravNode->data == value){
            StartingOutNeighborNode = graphTravNode;
            //If StartingINNeighborNode is not null return the count; otherwise return 0
            return (StartingOutNeighborNode->outNeighbors ? StartingOutNeighborNode->outNeighbors->count: 0);
        }
    }return -1;


}

// Returns the number of nodes in the graph
// Returns -1 if the graph is NULL.
int graph_num_nodes(graph_t* g){
    if (g == NULL) {
        return -1;
    }
    return g->numNodes;
}

// Returns the number of edges in the graph,
// Returns -1 on if the graph is NULL
int graph_num_edges(graph_t* g){
    if (g == NULL){
        return -1;
    }
    return g->numEdges;
}

// Free graph
// Removes a graph and ALL of its elements from memory.
// This should be called before the program terminates.
// Make sure you free all the dll's too.
void free_graph(graph_t* g){
    if (g == NULL) return;

    if (g->nodes && g->nodes->tail){
        //Walks DLL from end point
        node_t* traversalNode = g->nodes->tail;
        while(traversalNode){
            node_t* previous  = traversalNode->previous; //Points to position before 
            graph_node_t* traversalGraphNode = traversalNode->data; //Accesses vertex within DLL

            if (traversalGraphNode){
                //Free outneighbors
                if(traversalGraphNode->outNeighbors){
                    node_t *e = traversalGraphNode->outNeighbors->head;
                    while(e){
                        node_t* next = e->next;
                        free(e);
                        e= next;
                    }
                    free(traversalGraphNode->outNeighbors);
                }
            if(traversalGraphNode->inNeighbors){
                node_t* e = traversalGraphNode->inNeighbors->head;
                while(e){
                    node_t* next = e->next;
                    free(e);
                    e = next;
                }
                free(traversalGraphNode->inNeighbors);;
            }
            free(traversalGraphNode);
            }
            free(traversalNode);
            traversalNode = previous;
        }
    }
    if (g->nodes){
        free(g->nodes);
    }
    free(g);
}

#endif
