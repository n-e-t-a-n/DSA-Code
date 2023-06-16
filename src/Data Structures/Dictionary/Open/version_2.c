/*
Dictionary is a structure containing an array of pointers to heap nodes
and a pointer to the virtual heap
Note: each pointer points to the address of the first node in the list,
      NULL if there are no nodes in the list
*/

#include <stdio.h>

#define SIZE 10
#define MAX 0xFF

typedef int dictNode;

typedef struct {
    int data;
    int next;
} node; // Definition of node type in the virtual heap

typedef struct {
    node VH_node[MAX];
    int avail;
} VHeap; // Definition of the virtual heap as a structure with an array
         // of nodes and an integer pointing to the next available index

typedef struct {
    dictNode bucket[SIZE];
    VHeap *heapPtr;
} Dictionary; // Dictionary is a structure containing an array of cursor nodes
              // and a pointer to the virtual heap

VHeap initializeVHeap(); // Returns a newly initialized virtual heap with linked nodes
Dictionary initializeDict(VHeap* vh); // Returns an empty dictionary
void insert(Dictionary* d, int key); // Inserts a key into the dictionary
void destroy(Dictionary* d, int key); // Removes a key from the dictionary 
int member(Dictionary d, int key); // Returns 1 if the dictionary contains the specified key, 0 otherwise
int size(Dictionary d); // Returns the number of keys in the dictionary
void display(Dictionary d); // Displays the keys of the dictionary
int hash(int key); // Converts the given key into an indexable value in the dictionary

int mallocInVHeap(VHeap* vh); // Returns the next available index in the virtual heap
void freeInVHeap(dictNode idx, VHeap* vh); // Sets the "avail" property of the virutal heap to the given index

int main() {
    VHeap heap = initializeVHeap();
    Dictionary dict = initializeDict(&heap);
    int option, element;

    do {
        printf("\nList ADT Operations:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Member\n");
        printf("4. Size\n");
        printf("5. Display\n");
        printf("6. Exit\n");
        printf("Enter your option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Enter the key to insert: ");
                scanf("%d", &element);
                insert(&dict, element);
                break;
            case 2:
                printf("Enter the key to destroy: ");
                scanf("%d", &element);
                destroy(&dict, element);
                break;
            case 3:
                printf("Enter the key to check membership: ");
                scanf("%d", &element);
                if (member(dict, element)) {
                    printf("Element %d is a member of the dictionary.\n", element);
                } else {
                    printf("Element %d is not a member of the dictionary.\n", element);
                }
                break;
            case 4:
                printf("Size of the dictionary is %d.\n", size(dict));
                break;
            case 5:
                printf("Keys of the dictionary: \n");
                display(dict);
                printf("\n");
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

VHeap initializeVHeap() {
    VHeap newHeap = {{}, MAX-1};

    int temp;
    for (temp=MAX-1 ; temp!=-1 ; temp--) {
        newHeap.VH_node[temp].next = temp-1;
    }

    return newHeap;
}

Dictionary initializeDict(VHeap* vh) {
    Dictionary newDict = {{}, vh};
    int temp;

    for (temp=0 ; temp<SIZE ; temp++) {
        newDict.bucket[temp] = -1;
    }

    return newDict;
}

void insert(Dictionary* d, int key) {
    if (!member(*d, key)) {
        int hashValue = hash(key);
        dictNode *trav;

        for (trav=&d->bucket[hashValue] ; *trav!=-1 ; trav=&d->heapPtr->VH_node[*trav].next) {}

        dictNode newNode = mallocInVHeap(d->heapPtr);

        if (newNode!=-1) {
            d->heapPtr->VH_node[newNode].data = key;
            d->heapPtr->VH_node[newNode].next = *trav;

            *trav = newNode;
        }
    }
}

void destroy(Dictionary* d, int key) {
    if (member(*d, key)) {
        int hashValue = hash(key);
        dictNode *trav, temp;

        for (trav=&d->bucket[hashValue] ; d->heapPtr->VH_node[*trav].data!=key ; trav=&d->heapPtr->VH_node[*trav].next) {}

        temp = *trav;
        *trav = d->heapPtr->VH_node[*trav].next;

        freeInVHeap(temp, d->heapPtr);
    }
}

int member(Dictionary d, int key) {
    int hashValue = hash(key);
    dictNode trav;

    for(trav=d.bucket[hashValue] ; trav!=-1 && d.heapPtr->VH_node[trav].data!=key; trav=d.heapPtr->VH_node[trav].next) {}

    return trav!=-1;
}

int size(Dictionary d) {
    int size = 0, temp;
    dictNode trav;

    for (temp=0 ; temp<SIZE ; temp++) {
        for (trav=d.bucket[temp] ; trav!=-1 ; trav=d.heapPtr->VH_node[trav].next) {
            size++;
        }
    }

    return size;
}

void display(Dictionary d) {
    int temp;
    dictNode trav;

    for (temp=0 ; temp<SIZE ; temp++) {
        printf("Group %d: ", temp);

        for (trav=d.bucket[temp] ; trav!=-1 ; trav=d.heapPtr->VH_node[trav].next) {
            printf("%d ", d.heapPtr->VH_node[trav].data);
        }

        printf("\n");
    }
}

int hash(int key) {
    return key % SIZE;
}

int mallocInVHeap(VHeap* vh) {
    int allocatedNode = vh->avail;

    if (allocatedNode!=-1) {
        vh->avail = vh->VH_node[vh->avail].next;
    }

    return allocatedNode;
}

void freeInVHeap(dictNode idx, VHeap* vh) {
    vh->VH_node[idx].next = vh->avail;
    vh->avail = idx;
}