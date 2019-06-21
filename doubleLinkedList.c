#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "timer.c"

typedef struct Node{
    int data;
    struct Node* next;
    struct Node* prev;
}Node;

typedef struct List{
    struct Node* front;
    struct Node* back;
    int size;
}List;

//creates an empty list
List* createList(void){
    List* l = malloc(sizeof(List));
    assert(l);
    l -> size = 0;
    l -> front = NULL;
    l -> back = NULL;

    return l;
}

Node *createNode(const int theData){
    Node *n = malloc(sizeof(Node));
    assert(n);
    n -> data = theData;
    n -> next = NULL;
    n -> prev = NULL;
}

//adds a node with the given data to the front of the list
void addNodeFront(List* l, const int new_data){
    assert(l);
    
    Node* newNode = createNode(new_data);

    if(l -> size == 0)
    {
        l->front = newNode;
        l->back = newNode;
    }
    else
    {
        newNode -> next = l-> front;
        l-> front -> prev = newNode;
    
        l -> front = newNode;
    }
    l->size++;
  
    
}

//adds a node with the given data to the back of the list
void addNodeBack(List* l, const int new_data)
{
    assert(l);
    Node* newNode = createNode(new_data);
    
    if(l -> size == 0){
        l->front = newNode;
        l->back = newNode;
    }
    else{
        newNode -> prev = l -> back;
        l -> back -> next = newNode;
        l -> back = newNode;
    }
    l->size++;
}

//void removeNode(){}

void printList(const List* list){
   
    Node* currentNode = list -> front;
    printf("\nTraversal in forward direction \n");
    while(currentNode != NULL){
        printf(" %d ", currentNode->data);
        currentNode = currentNode -> next;
    }
}

void removeNode(List* l, const int key){

    Node* currentNode = l->front;
    
    while(currentNode != NULL){
       
       if( currentNode -> data == key )
       {
         //need to remove it  
         Node * n = currentNode -> next;
         Node* p = currentNode -> prev;
         
         if (currentNode != l -> back)
            n -> prev = p;
         else
             l -> back = p;
         
         
         if(currentNode != l -> front)
            p -> next = n;
         else
            l -> front = n;
         
         currentNode -> prev = NULL;
         currentNode -> next = NULL;
         
         l->size--;
         free(currentNode);
         
         break;
       }
       
       currentNode = currentNode -> next;
    }
    
}

Node* serach(List* l, const int key){
    Node* currentNode = l->front;
    
    while(currentNode != NULL){
        if(currentNode -> data = key)
            return currentNode;
        currentNode = currentNode -> next;
    }
    return NULL;
}

Node* returnFirstNode(List* l){
    assert(l);
    return l->front;
}

Node* returnLastNode(List* l){
    assert(l);
    return l->back;
}

Node* returnPreviousNode(Node* n){
    assert(n);
    return n -> prev;
}

Node* returnNextNode(Node* n){
    assert(n);
    return n -> next;
}

int main(int argc, char* argv[]){
    int n = -1;
    if(argc == 2)
        n = atoi(argv[1]);
    else{
        fprintf(stderr, "usage:%s <n> \n", argv[0]);
        fprintf(stderr, "where <n> is the n different sized list\n");
        //return -1;
    }
    stopwatch_init();
    struct stopwatch_t* timer = stopwatch_create (); assert (timer);
    
    List *l = createList();
    
    time_t t;
    srand((unsigned)time(&t));
    
    int i;
    int random_num = 0;
    for(i=0; i<n; i++){
        addNodeBack(l, i+1);
    }
    
    stopwatch_start (timer);
    for(i=0; i<10000; i++){
        random_num = rand()%n + 1;
        removeNode(l, random_num);
        addNodeFront(l, random_num);
    }
    
        
    long double t_qs = stopwatch_stop (timer);
    printf("n = %d\n", n);
    printf("\nt_qs = %Lg seconds \n", t_qs);
    
    
    return 0;
}
