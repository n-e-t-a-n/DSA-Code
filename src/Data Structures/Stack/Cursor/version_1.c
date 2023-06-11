/*
Stack is an integer pointing to the top element of a stack represented in a 
cursor based singly-linked list inside of a virtual heap. 
*/

#include <stdio.h>

#define MAX 0xFF

typedef int Stack; // Definition of stack

typedef struct {
    int data;
    Stack next;
} node; // Definition of node type in the virtual heap

typedef struct {
    node VH_node[MAX];
    Stack avail;
} VHeap; // Definition of the virtual heap as a structure with an array
         // of nodes and an integer pointing to the next available index

VHeap initializeVHeap(); // Returns a newly initialized virtual heap with linked nodes
Stack initializeStack(); // Returns an empty stack
void push(Stack* s, int elem, VHeap* vh); // Inserts element at the top of the stack
int pop(Stack* s, VHeap* vh); // Deletes top element of stack and returns it
int top(Stack s, VHeap vh); // Returns the top element of the stack
int isEmpty(Stack s); // Returns 1 if the stack is empty, 0 otherwise
int isFull(VHeap vh); // Returns 1 if the virtual heap is full, 0 otherwise
void display(Stack s, VHeap vh); // Displays the elements of the stack 

int mallocInVHeap(VHeap* vh); // Returns the next available index in the virtual heap
void freeInVHeap(Stack idx, VHeap* vh); // Sets the "avail" property of the virutal heap to the given index


int main() {
    VHeap heap = initializeVHeap();
    Stack stack = initializeStack();
    int option, element;

    do {
        printf("\n Stack ADT Operations:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Top\n");
        printf("4. IsEmpty\n");
        printf("5. IsFull\n");
        printf("6. Display\n");
        printf("7. Exit\n");
        printf("Enter your option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Enter the element to push: ");
                scanf("%d", &element);
                push(&stack, element, &heap);
                break;
            case 2:
                if (isEmpty(stack)) {
                    printf("There are no elements in the stack.\n");
                } else {
                    printf("%d has been popped off the stack.\n", pop(&stack, &heap));
                }
                break;
            case 3:
                if (isEmpty(stack)) {
                    printf("There are no elements in the stack.\n");
                } else {
                    printf("The element at the top of the stack is %d.\n", top(stack, heap));
                }
                break;
            case 4:
                printf("The stack is%sempty.\n", isEmpty(stack) ? " " : " not ");
                break;
            case 5:
                printf("The virtual heap is%sfull.\n", isFull(heap) ? " " : " not ");
                break;
            case 6:
                printf("Elements of the stack: ");
                display(stack, heap);
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

VHeap initializeVHeap() {
    VHeap newHeap = {{}, MAX-1};
    int temp;

    for (temp=MAX-1 ; temp!=-1 ; temp--) {
        newHeap.VH_node[temp].next = temp-1;
    }   

    return newHeap;
}

Stack initializeStack() {
    Stack newStack = -1;
    
    return newStack;
}

void push(Stack* s, int elem, VHeap* vh) {
    if (!isFull(*vh)) {
        Stack newNode = mallocInVHeap(vh);

        if (newNode!=-1) {
            vh->VH_node[newNode].data = elem;
            vh->VH_node[newNode].next = *s;

            *s = newNode;
        }
    }
}

int pop(Stack* s, VHeap* vh) {
    if (!isEmpty(*s)) {
        int poppedElem = vh->VH_node[*s].data;

        Stack temp = *s;
        *s = vh->VH_node[*s].next;

        freeInVHeap(temp, vh);

        return poppedElem;
    }
}

int top(Stack s, VHeap vh) {
    if (!isEmpty(s)) {
        return vh.VH_node[s].data;
    }
}

int isEmpty(Stack s) {
    return s==-1;
}

int isFull(VHeap vh) {
    return vh.avail==-1;
}

void display(Stack s, VHeap vh) {
    Stack buffer = initializeStack(); // Auxilliary stack to store elements of the stack in reverse

    while (!isEmpty(s)) {
        push(&buffer, pop(&s, &vh), &vh); // Push popped elements to the buffer stack
    }

    while (!isEmpty(buffer)) {
        printf("%d ", top(buffer, vh));
        push(&s, pop(&buffer, &vh), &vh); // Push elements back to original stack
    }
}

int mallocInVHeap(VHeap* vh) {
    Stack allocatedNode = vh->avail;

    if (allocatedNode!=-1) {
        vh->avail = vh->VH_node[vh->avail].next;
    }

    return allocatedNode;
}

void freeInVHeap(Stack idx, VHeap* vh) {
    vh->VH_node[idx].next = vh->avail;
    vh->avail = idx;
}