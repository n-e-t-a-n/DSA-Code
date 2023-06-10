/*
List is a structure containing an array and variable count
Note: count represents the actual number of elements in the array
      If MAX is the size of the array, count <= MAX
*/

#include <stdio.h>
#include <string.h>

#define MAX 0xFF // 255 in Hexadecimal

typedef struct {
    int array[MAX], count; // Array with a size of MAX and a variable count
} List; 

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
    List newList = {{}, 0};
    
    return newList;
}

void insert(List* l, int elem) {
    if (l->count<MAX) {
        l->array[l->count++] = elem;
    }
}

void destroy(List* l, int elem) {
    int temp;

    for (temp=0 ; temp<l->count && l->array[temp]!=elem ; temp++) {}

    if (temp<l->count) {
        memcpy(&l->array[temp], &l->array[temp+1], (l->count-temp-1) * sizeof(int));
        l->count--;
    }
}

int member(List l, int elem) {
    int temp;

    for (temp=0 ; temp<l.count && l.array[temp]!=elem ; temp++) {}

    return temp<l.count;
}

int locate(List l, int elem) {
    int temp;

    for (temp=0 ; temp<l.count && l.array[temp]!=elem ; temp++) {}

    return temp<l.count ? temp : -1;
}

int size(List l) {
    return l.count;
}

void display(List l) {
    int temp;

    for (temp=0 ; temp<l.count ; temp++) {
        printf("%d ", l.array[temp]);
    }
}