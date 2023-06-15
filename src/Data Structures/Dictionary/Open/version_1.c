/*
Dictionary is a structure containing an array of pointers to linked list nodes
Note: each pointer points to the address of the first node in the list,
      NULL if there are no nodes in the list
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 4

typedef struct node {
    int data;
    struct node *next;
}* node;

typedef node* Dictionary;

Dictionary initialize(); // Returns an empty dictionary
void insert(Dictionary d, int key); // Inserts a key into the dictionary
void destroy(Dictionary d, int key); // Removes a key from the dictionary 
int member(Dictionary d, int key); // Returns 1 if the dictionary contains the specified key, 0 otherwise
int size(Dictionary d); // Returns the number of keys in the dictionary
void display(Dictionary d); // Displays the keys of the dictionary
int hash(int key); // Converts the given key into an indexable value in the dictionary

int main() {
    Dictionary dict = initialize();
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
                insert(dict, element);
                break;
            case 2:
                printf("Enter the key to destroy: ");
                scanf("%d", &element);
                destroy(dict, element);
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

Dictionary initialize() {
    Dictionary newDict = (Dictionary) malloc(sizeof(node)*MAX);

    int temp;

    for (temp=0 ; temp<MAX; temp++) {
        newDict[temp] = NULL;
    }

    return newDict;
}

void insert(Dictionary d, int key) {
    if (!member(d, key)) {
        int hashValue = hash(key);
        node *trav;

        for (trav=&d[hashValue] ; *trav!=NULL ; trav=&(*trav)->next) {}

        node newNode = (node) malloc(sizeof(struct node));

        if (newNode!=NULL) {
            newNode->data = key;
            newNode->next = *trav;

            *trav = newNode;
        }
    }
}

void destroy(Dictionary d, int key) {
    if (member(d, key)) {
        int hashValue = hash(key);
        node *trav, temp;

        for (trav=&d[hashValue] ; (*trav)->data!=key ; trav=&(*trav)->next) {}

        temp = *trav;
        *trav = (*trav)->next;

        free(temp);
        temp = NULL;
    }
}

int member(Dictionary d, int key) {
    int hashValue = hash(key);
    node trav;

    for(trav=d[hashValue] ; trav!=NULL && trav->data!=key; trav=trav->next) {}

    return trav!=NULL;
}

int size(Dictionary d) {
    int size = 0, temp;
    node trav;

    for (temp=0 ; temp<MAX ; temp++) {
        for (trav=d[temp] ; trav!=NULL ; trav=trav->next) {
            size++;
        }
    }

    return size;
}

void display(Dictionary d) {
    int temp;
    node trav;

    for (temp=0 ; temp<MAX ; temp++) {
        printf("Group %d: ", temp);

        for (trav=d[temp] ; trav!=NULL ; trav=trav->next) {
            printf("%d ", trav->data);
        }

        printf("\n");
    }
}

int hash(int key) {
    return key % MAX;
}
