/*
Set is a pointer to a dynamically allocated array of characters with size MAX
Note: char is used as it is the smallest datatype in C 
      (but you can use any other datatype to represent the bits in the array)
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 64 // Size of the bit-vector array

typedef char* Set; // Definition of set

Set initialize(); // Returns an empty set
void insert(Set s, int elem); // Inserts element at the top of the stack
void destroy(Set s, int elem); // Removes given element from the set if present
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
                    insert(set1, element);
                } else {
                    insert(set2, element);
                }
                
                break;
            case 2:
                printf("Enter the element to delete: ");
                scanf("%d", &element);

                printf("Which set would you like to perform this operation on? 1 or 2: ");
                scanf("%d", &setOption);
                
                if (setOption==1) {
                    destroy(set1, element);
                } else {
                    destroy(set2, element);
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
                Set setUnion = unite(set1, set2);
                display(setUnion);
                free(setUnion);
                break;
            case 5:
                printf("The intersection of the two sets is: ");
                Set setIntersection = intersect(set1, set2);
                display(setIntersection);
                free(setIntersection);
                break;
            case 6:
                printf("The difference of the two sets is: ");
                Set setDifference = difference(set1, set2);
                display(setDifference);
                free(setDifference);
                break;
            case 7:
                printf("Which set would you like to perform this operation on? 1 or 2: ");
                scanf("%d", &setOption);

                if (setOption==1) {
                    printf("The complement of set 1 is: ");
                    Set setComplement = complement(set1);
                    display(setComplement);
                    free(setComplement);
                } else {
                    printf("The complement of set 2 is: ");
                    Set setComplement = complement(set2);
                    display(setComplement);
                    free(setComplement);
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
    Set newSet = (Set) calloc(MAX, sizeof(char));

    return newSet;
}

void insert(Set s, int elem) {
    s[elem] = 1;
}

void destroy(Set s, int elem) {
    s[elem] = 0;
}

int member(Set s, int elem) {
    return s[elem];
}

Set unite(Set s1, Set s2) {
    Set setUnion = initialize();
    int temp;

    for (temp=0 ; temp<MAX ; temp++) {
        setUnion[temp] = s1[temp] || s2[temp];
    }

    return setUnion;
} 

Set intersect(Set s1, Set s2) {
    Set setIntersection = initialize();
    int temp;

    for (temp=0 ; temp<MAX ; temp++) {
        setIntersection[temp] = s1[temp] && s2[temp];
    }

    return setIntersection;
}

Set difference(Set s1, Set s2) {
    Set setDifference = initialize();
    int temp;

    for (temp=0 ; temp<MAX ; temp++) {
        setDifference[temp] = s1[temp] && !s2[temp];
    }

    return setDifference;
}

Set complement(Set s) {
    Set setComplement = initialize();
    int temp;

    for (temp=0 ; temp<MAX ; temp++) {
        setComplement[temp] = !s[temp];
    }

    return setComplement;
}

void display(Set s) {
    int temp;

    for (temp=0 ; temp<MAX ; temp++) {
        if (s[temp]) {
            printf("%d ", temp);
        }
    }
}