#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "timer.c"
#include <assert.h>

typedef struct QueueNode{
    float data;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue{    
    struct QueueNode* head;
    struct QueueNode* tail;
} Queue;
    

void printNode(QueueNode *qnode){
    while(qnode != NULL){
        printf("%f\n", qnode->data);
        qnode = qnode->next;
    }
}

void Dequeue(struct Queue* q){
    if(q->head == NULL) return;
    
    QueueNode* temp = q -> head;
    if(q->head == q->tail)
        q->head = q->tail = NULL;
    else{
        q->head = q-> head -> next;
    }
    
    free(temp);
}

void Enqueue(struct Queue* q, float x){
    QueueNode* newNode = malloc(sizeof(QueueNode));
    newNode -> data = x;
    newNode -> next = NULL;

    if(q -> head == NULL && q  -> tail == NULL){
        q -> head = q-> tail = newNode;
    }
    else{
        q -> tail -> next = newNode;
        q -> tail = newNode;
    }
}
 
 

int main(int argc, char* argv[]){
    int n = -1;
    int t = -1;
    float rand_num = 0;
    float a = 5.0;
    if(argc == 3){
        n = atoi(argv[1]);
        t = atoi(argv[2]);
    }else{
        fprintf(stderr, "usage: %s <n> <t>\n", argv[0]);
        fprintf(stderr, "where <n> is the n random floating point numbers into the queue.\n");
        fprintf(stderr, "where <t> is the time you enqueue x.\n");
        return -1;
    }
    
// timer
    stopwatch_init();
    struct stopwatch_t* timer = stopwatch_create (); assert (timer);
   
//1. (a) create an empty queue    
    Queue *q = malloc(sizeof(Queue));
    Queue *temp = malloc(sizeof(Queue));

//2. Enqueue random floating point numbers into the queue
    srand((unsigned int)time(NULL));
    
    int i=0;
    for(i = 0; i < n; i++){
        rand_num = ((float)rand()/(float)(RAND_MAX))*a;
    //    printf("%d floating number is %f\n", i+1, rand_num);
        Enqueue(q, rand_num);
        
    }
    
    stopwatch_start (timer);
    for(i = 0; i < t; i++){
        float temp = q -> head -> data;
   //      printf("%d floating number is %f\n", i+1, temp);
        Dequeue(q);
        Enqueue(q, temp);
    }
    
    long double t_qs = stopwatch_stop (timer);
    printf("n = %d\nt = %d\n\n", n, t);
    printf("\nt_qs = %Lg seconds \nt_qs/t = %Lg\n", t_qs, t_qs/t);
    
    

    return 0;
}
