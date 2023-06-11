/*
Stack is a pointer to a structure which represents the top of the stack with a 
data variable pointer to the next node in the stack.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next; // Pointer to the next node in the stack
}* Stack; // Pointer to top of stack

Stack initialize(); // Returns an empty stack
void push(Stack* s, int elem); // Inserts element at the top of the stack
int pop(Stack* s); // Deletes top element of stack and returns it
int top(Stack s); // Returns the top element of the stack
int isEmpty(Stack s); // Returns 1 if the stack is empty, 0 otherwise
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
        printf("5. Display\n");
        printf("6. Exit\n");
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
                printf("Elements of the stack: ");
                display(stack);
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

Stack initialize() {
    Stack newStack = NULL;
    
    return newStack;
}

void push(Stack* s, int elem) {
    Stack newNode = (Stack) malloc(sizeof(struct node));

    if (newNode!=NULL) {
        newNode->data = elem;
        newNode->next = *s;

        *s = newNode;
    }
}

int pop(Stack* s) {
    if (!isEmpty(*s)) {
        int poppedElem = top(*s);

        Stack temp = *s;
        *s = (*s)->next;

        free(temp);

        return poppedElem;
    }
}

int top(Stack s) {
    if (!isEmpty(s)) {
        return s->data;
    }
}

int isEmpty(Stack s) {
    return s==NULL;
}

void display(Stack s) {
    if (s!=NULL) {
        display(s->next);
        printf("%d ", s->data);
    }
}