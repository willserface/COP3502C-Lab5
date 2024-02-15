/// Will Serface - COP3502C Lab 4

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char letter;
    struct node *next;
} node;

// Returns number of nodes in the linkedList.
int length(node *head) {
    if (head == NULL) return 0; // Check for NULL

    // Variables to track position in LL
    int count = 1; // Number of nodes in list
    node *current = head; // Current node

    // Increment variables until last item
    while (current->next != NULL) {
        count++;
        current = current->next;
    }

    // Return number of nodes in LL
    return count;
}

// parses the string in the linkedList
//  if the linked list is head -> |a|->|b|->|c|
//  then toCString function wil return "abc"
char *toCString(node *head) {
    // Get length of LL plus NULL terminator
    int len = length(head) + 1;

    // Create and Allocate memory for output
    char *output = malloc(len);

    // Current node in LL, starting from head
    node *current = head;

    // Counter for current position in string
    int i = 0;

    // Repeat for each item in LL
    while (current != NULL) {
        // Set current letter
        output[i] = current->letter;

        // Increment Variables
        current = current->next;
        i++;
    }

    // Add NULL terminator
    output[i] = '\0';

    // Return output
    return output;
}

// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as follows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node **pHead, char c) {
    // Check if pHead is NULL
    if (pHead == NULL) return;

    // Check if head node is last node
    if (*pHead == NULL) {
        // Allocate head
        *pHead = malloc(sizeof(node));

        // Initialize head
        (*pHead)->letter = c;
        (*pHead)->next = NULL;
    } else {
        // Go to last node
        node *last = *pHead;
        while (last->next != NULL) last = last->next;

        // Create and initialize new node
        node *end = malloc(sizeof(node));
        *end = (node) {c, NULL};

        // Add new node to end of LL
        last->next = end;
    }
}

// deletes all nodes in the linkedList.
void deleteList(node **pHead) {
    // Check for NULL
    if (pHead == NULL) return;

    // Pointer to next node and node to be deleted
    node *next = *pHead, *current = next;

    // Follow to end of LL
    while (next != NULL) {
        // Prepare to current next node
        current = next;

        // Increment next pointer
        next = next->next;

        // Clear pointer from next node
        current->next = NULL;

        // Free memory at next node
        free(current);

        // Clear pointer
        current = NULL;
    }

    // Clear head
    *pHead = NULL;
}

int main(void) {
    int i, strLen, numInputs;
    node *head = NULL;
    char *str;
    char c;
    FILE *inFile = fopen("input.txt", "r");

    fscanf(inFile, " %d\n", &numInputs);

    while (numInputs-- > 0) {
        fscanf(inFile, " %d\n", &strLen);
        for (i = 0; i < strLen; i++) {
            fscanf(inFile, " %c", &c);
            insertChar(&head, c);
        }

        str = toCString(head);
        printf("String is : %s\n", str);

        free(str);
        deleteList(&head);

        if (head != NULL) {
            printf("deleteList is not correct!");
            break;
        }
    }

    fclose(inFile);
}