/*
Set is a specific datatype representing a computer word
*/

#include <stdio.h>

typedef unsigned long long int Set; // Definition of set

const int SIZE = sizeof(Set)*8; // Constant global variable representing 
                                // the number of bits in the set variable

Set initialize(); // Returns an empty set
void insert(Set* s, int elem); // Inserts element at the top of the stack
void destroy(Set* s, int elem); // Removes given element from the set if present
int member(Set s, int elem); // Returns 1 if element is in the set, 0 otherwise
Set unite(Set s1, Set s2); // returns the union of set 1 and 2
Set intersect(Set s1, Set s2); // Returns the intersection of set 1 and 2
Set difference(Set s1, Set s2); // Returns the difference of set 1 and 2
Set complement(Set s); // Returns the complement of a given set
void display(Set s); // Displays the elements of the set

int main() {
    Set set1 = initialize();
    Set set2 = initialize();
    int option, element, setOption;

    do {
        printf("\nList ADT Operations:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Member\n");
        printf("4. Unite\n");
        printf("5. Intersect\n");
        printf("6. Difference\n");
        printf("7. Complement\n");
        printf("8. Display\n");
        printf("9. Exit\n");
        printf("Enter your option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Enter the element to insert: ");
                scanf("%d", &element);

                printf("Which set would you like to perform this operation on? 1 or 2: ");
                scanf("%d", &setOption);

                if (setOption==1) {
                    insert(&set1, element);
                } else {
                    insert(&set2, element);
                }
                
                break;
            case 2:
                printf("Enter the element to delete: ");
                scanf("%d", &element);

                printf("Which set would you like to perform this operation on? 1 or 2: ");
                scanf("%d", &setOption);
                
                if (setOption==1) {
                    destroy(&set1, element);
                } else {
                    destroy(&set2, element);
                }

                break;
            case 3:
                printf("Enter the element to check membership: ");
                scanf("%d", &element);

                printf("Which set would you like to perform this operation on? 1 or 2: ");
                scanf("%d", &setOption);
                
                if (setOption==1) {
                    printf("%d is%sa member of set 1.", element, member(set1, element) ? " " : " not ");
                } else {
                    printf("%d is%sa member of set 2.", element, member(set2, element) ? " " : " not ");
                }
                
                break;
            case 4:
                printf("The union of the two sets is: ");
                display(unite(set1, set2));
                break;
            case 5:
                printf("The intersection of the two sets is: ");
                display(intersect(set1, set2));
                break;
            case 6:
                printf("The difference of the two sets is: ");
                display(difference(set1, set2));
                break;
            case 7:
                printf("Which set would you like to perform this operation on? 1 or 2: ");
                scanf("%d", &setOption);

                if (setOption==1) {
                    printf("The complement of set 1 is: ");
                    display(complement(set1));
                } else {
                    printf("The complement of set 2 is: ");
                    display(complement(set2));
                }

                break;
            case 8: 
                printf("Which set would you like to perform this operation on? 1 or 2: ");
                scanf("%d", &setOption);

                if (setOption==1) {
                    printf("The elements of set 1 are: ");
                    display(set1);
                } else {
                    printf("The elements of set 2 are: ");
                    display(set2);
                }

                break;
            case 9:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    } while (option != 9);

    return 0;
}

Set initialize() {
    Set newSet = 0;

    return newSet;
}

void insert(Set* s, int elem) {
    *s |= 1<<elem;
}

void destroy(Set* s, int elem) {
    *s &= ~(1<<elem);
}

int member(Set s, int elem) {
    return s & 1<<elem;
}

Set unite(Set s1, Set s2) {
    return s1 | s2;
} 

Set intersect(Set s1, Set s2) {
    return s1 & s2;
}

Set difference(Set s1, Set s2) {
    return s1 & ~s2;
}

Set complement(Set s) {
    return ~s;
}

void display(Set s) {
    int temp;

    for (temp=0 ; temp<SIZE ; temp++) {
        if (s & (Set)1<<temp) {
            printf("%d ", temp);
        }
    }
}