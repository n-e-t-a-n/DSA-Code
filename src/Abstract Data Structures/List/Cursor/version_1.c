/*
List is an integer pointing to the first element of a list represented in a 
cursor based array inside of a virtual heap. 
*/

#include <stdio.h>

#define MAX 0xFF

typedef int List; // Definition of list

typedef struct {
    int data;
    List next;
} node; // Definition of node type in the virtual heap

typedef struct {
    node VH_node[MAX];
    List avail;
} VHeap; // Definition of the virtual heap as a structure with an array
         // of nodes and an integer pointing to the next available index

VHeap initializeVHeap(); // Returns a newly initialized virtual heap with linked nodes
List initializeList(); // Returns an empty list
void insert(List* l, int elem, VHeap* vh); // Inserts element at the end of the list
void destroy(List* l, int elem, VHeap* vh); // Deletes first instance of element in the list
int member(List l, int elem, VHeap vh); // Checks if element is in the list
int locate(List l, int elem, VHeap vh); // Returns position of element in the list
int size(List l, VHeap vh); // Returns the number of elements in the list
void display(List l, VHeap vh); // Displays the elements of the list

int mallocInVHeap(VHeap* vh); // Returns the next available index in the virtual heap
void freeInVHeap(List idx, VHeap* vh); // Sets the "avail" property of the virutal heap to the given index

int main() {
    VHeap heap = initializeVHeap();
    List list = initializeList();
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
                insert(&list, element, &heap);
                break;
            case 2:
                printf("Enter the element to destroy: ");
                scanf("%d", &element);
                destroy(&list, element, &heap);
                break;
            case 3:
                printf("Enter the element to check membership: ");
                scanf("%d", &element);
                if (member(list, element, heap)) {
                    printf("Element %d is a member of the list.\n", element);
                } else {
                    printf("Element %d is not a member of the list.\n", element);
                }
                break;
            case 4:
                printf("Enter the element to locate: ");
                scanf("%d", &element);
                int position = locate(list, element, heap);
                if (position != -1) {
                    printf("Element %d is located at position %d in the list.\n", element, position);
                } else {
                    printf("Element %d is not found in the list.\n", element);
                }
                break;
            case 5:
                printf("Size of the list is %d.\n", size(list, heap));
                break;
            case 6:
                printf("\nElements of the list: ");
                display(list, heap);
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

VHeap initializeVHeap() {
    VHeap newHeap = {{}, MAX-1};
    int temp;

    for (temp=MAX-1 ; temp!=-1 ; temp--) {
        newHeap.VH_node[temp].next = temp-1;
    }

    return newHeap;
}

List initializeList() {
    List newList = -1;

    return newList;
}

void insert(List* l, int elem, VHeap* vh) {
    List* trav;

    for (trav=l ; *trav!=-1 ; trav=&vh->VH_node[*trav].next) {}

    List newNode = mallocInVHeap(vh);

    if (newNode!=-1) {
        vh->VH_node[newNode].data = elem;
        vh->VH_node[newNode].next = *trav;

        *trav = newNode;

    }
}

void destroy(List* l, int elem, VHeap* vh) {
    List* trav;

    for (trav=l ; *trav!=-1 && vh->VH_node[*trav].data!=elem ; trav=&vh->VH_node[*trav].next) {}

    if (*trav!=-1) {
        List temp = *trav;
        *trav = vh->VH_node[temp].next;

        freeInVHeap(temp, vh);
    }
}

int member(List l, int elem, VHeap vh) {
    List temp;

    for (temp=l ; temp!=-1 && vh.VH_node[temp].data!=elem ; temp=vh.VH_node[temp].next) {}

    return temp!=-1;
}

int locate(List l, int elem, VHeap vh) {
    List temp;
    int position=0;

    for (temp=l ; temp!=-1 && vh.VH_node[temp].data!=elem ; temp=vh.VH_node[temp].next) {
        position++;
    }

    return temp!=-1 ? position : -1;
}

int size(List l, VHeap vh) {
    List temp;
    int count=0;

    for (temp=l ; temp!=-1 ; temp=vh.VH_node[temp].next) {
        count++;
    }

    return count;
}

void display(List l, VHeap vh) {
    List temp;

    for (temp=l ; temp!=-1 ; temp=vh.VH_node[temp].next) {
        printf("%d ", vh.VH_node[temp].data);
    }
}

int mallocInVHeap(VHeap* vh) {
    List allocatedNode = vh->avail;

    if (allocatedNode!=-1) {
        vh->avail = vh->VH_node[vh->avail].next;
    }

    return allocatedNode;
}

void freeInVHeap(List idx, VHeap* vh) {
    vh->VH_node[idx].next = vh->avail;
    vh->avail = idx;
}