/*
Queue is a pointer to a dynamically allocated node
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next; // Pointer to the next node in the
}* Queue; // Pointer to the front of the queue

Queue initialize(); // Returns an empty queue
void enqueue(Queue* q, int elem); // Inserts element at the rear of the queue
int dequeue(Queue* q); // Deletes the element at the front of the queue and returns it
int front(Queue q); // Returns the front element of the queue
int isEmpty(Queue q); // Returns 1 if the queue is empty, 0 otherwise
void display(Queue q); // Displays the elements of the queue (without traversal)

int main() {
    Queue queue = initialize();
    int option, element;

    do {
        printf("\n Queue ADT Operations:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Front\n");
        printf("4. IsEmpty\n");
        printf("5. Display\n");
        printf("6. Exit\n");
        printf("Enter your option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Enter the element to enqueue: ");
                scanf("%d", &element);
                enqueue(&queue, element);
                break;
            case 2:
                if (isEmpty(queue)) {
                    printf("There are no elements in the queue.\n");
                } else {
                    printf("%d has been dequeued.\n", dequeue(&queue));
                }
                break;
            case 3:
                if (isEmpty(queue)) {
                    printf("There are no elements in the queue.\n");
                } else {
                    printf("The element at the front of the queue is %d.\n", front(queue));
                }
                break;
            case 4:
                printf("The queue is%sempty.\n", isEmpty(queue) ? " " : " not ");
                break;
            case 5:
                printf("Elements of the queue: ");
                display(queue);
                break;
            case 6:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    } while (option != 6);

    return 0;
}

Queue initialize() {
    Queue newQueue = NULL;

    return newQueue;

    // Can also just return NULL to be more concise
}

void enqueue(Queue* q, int elem) {
    Queue* trav;

    for (trav=q ; *trav!=NULL ; trav=&(*trav)->next) {}

    Queue newNode = (Queue) malloc(sizeof(struct node));

    if (newNode!=NULL) {
        newNode->data = elem;
        newNode->next = *trav;

        *trav = newNode;
    }
}

int dequeue(Queue* q) {
    if (!isEmpty(*q)) {
        int removedElem = (*q)->data;

        Queue temp = *q; 
        *q = (*q)->next;

        free(temp);

        return removedElem;
    }
}

int front(Queue q) {
    if (!isEmpty(q)) {
        return q->data;
    }
}

int isEmpty(Queue q) {
    return q==NULL;
}

void display(Queue q) {
    Queue buffer = initialize(); 

    while(!isEmpty(q)) {
        enqueue(&buffer, dequeue(&q));
    }

    while(!isEmpty(buffer)) {
        printf("%d ", front(buffer));
        enqueue(&q, dequeue(&buffer));
    }
} 