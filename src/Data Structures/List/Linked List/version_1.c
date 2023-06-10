/*
List is a pointer to a structure containing an element and a 
pointer to the next node in the singly linked list.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next; // Pointer to the next node
}* List;

List initialize(); // Returns an empty list
void insert(List* l, int elem); // Inserts element at the end of the list
void destroy(List* l, int elem); // Deletes first instance of element in the list
int member(List l, int elem); // Checks if element is in the list
int locate(List l, int elem); // Returns position of element in the list
int size(List l); // Returns the number of elements in the list
void display(List l); // Displays the elements of the list


int main() {
    List list = initialize();
    int option, element;

    do {
        printf("\nList ADT Operations:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Member\n");
        printf("4. Locate\n");
        printf("5. Size\n");
        printf("6. Display\n");
        printf("7. Exit\n");
        printf("Enter your option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Enter the element to insert: ");
                scanf("%d", &element);
                insert(&list, element);
                break;
            case 2:
                printf("Enter the element to destroy: ");
                scanf("%d", &element);
                destroy(&list, element);
                break;
            case 3:
                printf("Enter the element to check membership: ");
                scanf("%d", &element);
                if (member(list, element)) {
                    printf("Element %d is a member of the list.\n", element);
                } else {
                    printf("Element %d is not a member of the list.\n", element);
                }
                break;
            case 4:
                printf("Enter the element to locate: ");
                scanf("%d", &element);
                int position = locate(list, element);
                if (position != -1) {
                    printf("Element %d is located at position %d in the list.\n", element, position);
                } else {
                    printf("Element %d is not found in the list.\n", element);
                }
                break;
            case 5:
                printf("Size of the list is %d.\n", size(list));
                break;
            case 6:
                printf("\nElements of the list: ");
                display(list);
                printf("\n");
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

List initialize() {
    List newList = NULL;

    return newList;

    // Alternatively, you can just return NULL
}

void insert(List* l, int elem) {
    List* trav;

    for (trav=l ; *trav!=NULL ; trav=&(*trav)->next) {} // Loops until end of list

    List newNode = (List) malloc(sizeof(struct node)); // Allocate memory for the new node on the heap

    if (newNode!=NULL) { // Check if malloc() was successful
        newNode->data = elem;
        newNode->next = *trav; // If inserting at the end of list, can just be [ = NULL ] directly

        *trav = newNode; // Append new node to the end of the list
    }    
}

void destroy(List* l, int elem) {
    List* trav;

    for (trav=l ; *trav!=NULL && (*trav)->data!=elem ; trav=&(*trav)->next) {} // Stops if element is found

    if (*trav!=NULL) { // Check if the element was in the list
        List temp = *trav;
        *trav = temp->next; // Sets trav to the next node, effectively removing element from the list

        free(temp); // Call free() to free data from heap and avoid memory leaks
    }
}

int member(List l, int elem) {
    List temp;

    for (temp=l ; temp!=NULL && temp->data!=elem ; temp=temp->next) {} // Stops if element is found

    return temp!=NULL; // Returns 1 if the element was in the list, 0 otherwise
}

int locate(List l, int elem) {
    List temp;
    int position=0;

    for (temp=l ; temp!=NULL && temp->data!=elem ; temp=temp->next) {
        position++; // Increment position variable
    } // Stops if element is found

    return temp!=NULL ? position : -1; // Returns position if the element was in the list, -1 otherwise
}

int size(List l) {
    List temp;
    int count=0;

    for (temp=l ; temp!=NULL ; temp=temp->next) {
        count++; // Increment count variable
    } // Stops when end of list is reached

    return count;
}

void display(List l) {
    List temp;

    for (temp=l ; temp!=NULL ; temp=temp->next) {
        printf("%d ", temp->data);
    }
}