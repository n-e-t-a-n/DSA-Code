/*
Stack is a structure containing an array and variable top
Note: top represents the index of the top element of the stack
      If MAX is the size of the array, top<=MAX-1
*/

#include <stdio.h>

#define MAX 0xFF // 255 in Hexadecimal

typedef struct {
    int array[MAX], top; // Array with a size of MAX and a variable top
} Stack; 

Stack initialize(); // Returns an empty stack
void push(Stack* s, int elem); // Inserts element at the top of the stack
int pop(Stack* s); // Deletes top element of stack and returns it
int top(Stack s); // Returns the top element of the stack
int isEmpty(Stack s); // Returns 1 if the stack is empty, 0 otherwise
int isFull(Stack s); // Returns 1 if the stack is full, 0 otherwise
int size(Stack s); // Returns the number of elements in the stack
void display(Stack s); // Displays the elements of the stack (without traversal)


int main() {
    Stack stack = initialize();
    int option, element;

    do {
        printf("\n Stack ADT Operations:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Top\n");
        printf("4. IsEmpty\n");
        printf("5. IsFull\n");
        printf("6. Size\n");
        printf("7. Display\n");
        printf("8. Exit\n");
        printf("Enter your option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Enter the element to push: ");
                scanf("%d", &element);
                push(&stack, element);
                break;
            case 2:
                if (isEmpty(stack)) {
                    printf("There are no elements in the stack.\n");
                } else {
                    printf("%d has been popped off the stack.\n", pop(&stack));
                }
                break;
            case 3:
                if (isEmpty(stack)) {
                    printf("There are no elements in the stack.\n");
                } else {
                    printf("The element at the top of the stack is %d.\n", top(stack));
                }
                break;
            case 4:
                printf("The stack is%sempty.\n", isEmpty(stack) ? " " : " not ");
                break;
            case 5:
                printf("The stack is%sfull.\n", isFull(stack) ? " " : " not ");
                break;
            case 6:
                printf("Size of the stack is %d.\n", size(stack));
                break;
            case 7:
                printf("\nElements of the stack: ");
                display(stack);
                printf("\n");
                break;
            case 8:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    } while (option != 8);

    return 0;
}

Stack initialize() {
    Stack newStack = {{}, -1};
    
    return newStack;
}

void push(Stack* s, int elem) {
    if (!isFull(*s)) {
        s->array[++s->top] = elem;
    }
}

int pop(Stack* s) {
    if (!isEmpty(*s)) {
        return s->array[s->top--];
    }
}

int top(Stack s) {
    if (!isEmpty(s)) {
        return s.array[s.top];
    }
}

int isEmpty(Stack s) {
    return s.top==-1;
}

int isFull(Stack s) {
    return s.top==MAX-1;
}

int size(Stack s) {
    return s.top+1;
}

void display(Stack s) {
    Stack buffer; // Auxilliary stack to store elements of the stack in reverse
    initialize(&buffer);

    while (!isEmpty(s)) {
        push(&buffer, pop(&s)); // Push popped elements to the buffer stack
    }

    while (!isEmpty(buffer)) {
        printf("%d ", top(buffer));
        push(&s, pop(&buffer)); // Push elements back to original stack
    }

    // An easier method is to use a for loop, but this is for 
    // if the stack is not meant to be traversed
}