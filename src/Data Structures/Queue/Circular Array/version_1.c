/*
Queue is a structure containing an array, the index of the element at the 
front of the queue, and a count variable
*/

#include <stdio.h>

#define MAX 0xFF // 255 in Hexadecimal

typedef struct {
    int array[MAX], front, count;
} Queue; 

Queue initialize(); // Returns an empty queue
void enqueue(Queue* q, int elem); // Inserts element at the rear of the queue
int dequeue(Queue* q); // Deletes the element at the front of the queue and returns it
int front(Queue q); // Returns the front element of the queue
int isEmpty(Queue q); // Returns 1 if the queue is empty, 0 otherwise
int isFull(Queue q); // Returns 1 if the queue is full, 0 otherwise
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
        printf("5. IsFull\n");
        printf("6. Display\n");
        printf("7. Exit\n");
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
                printf("The queue is%sfull.\n", isFull(queue) ? " " : " not ");
                break;
            case 6:
                printf("Elements of the queue: ");
                display(queue);
                break;
            case 7:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    } while (option != 7);

    return 0;
}

Queue initialize() {
    Queue newQueue = {0}; // Initialize array, top, and count to 0

    return newQueue;

}

void enqueue(Queue* q, int elem) {
    if (!isFull(*q)) {
        q->array[(q->front+q->count++)%MAX] = elem;
    }
}

int dequeue(Queue* q) {
    if (!isEmpty(*q)) {
        int removedElem = q->array[q->front%MAX];

        q->front++;
        q->count--;

        return removedElem;
    }
}

int front(Queue q) {
    if (!isEmpty(q)) {
        return q.array[q.front%MAX];
    }
}

int isEmpty(Queue q) {
    return q.count==0;
}

int isFull(Queue q) {
    return q.count==MAX;
}

void display(Queue q) {
    Queue buffer = initialize();

    while (!isEmpty(q)) {
        enqueue(&buffer, dequeue(&q));
    }

    while(!isEmpty(buffer)) {
        printf("%d ", front(buffer));
        enqueue(&q, dequeue(&buffer));
    }
} 