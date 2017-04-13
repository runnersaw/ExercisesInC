/* Example code for Exercises in C.

Based on an example from http://www.learn-c.org/en/Linked_lists

Copyright 2016 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *next;
} Node;


/* Makes a new node structure.
 *
 * val: value to store in the node.
 * next: pointer to the next node
 *
 * returns: pointer to a new node
 */
Node *make_node(int val, Node *next) {
    Node *node = malloc(sizeof(Node));
    node->val = val;
    node->next = next;
    return node;
}


/* Prints the values in a list.
 *
 * list: pointer to pointer to Node
 */
void print_list(Node **list) {
    Node *current = *list;

    printf("[ ");
    while (current != NULL) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("]\n");
}


/* Removes and returns the first element of a list.
 *
 * list: pointer to pointer to Node
 *
 * returns: int or -1 if the list is empty
 */
int pop(Node **list) {
    // Get the head. If it's empty, return -1.
    Node *head = *list;
    if (head == NULL) {
        return -1;
    }

    // Get the next, and make it the new first element of the list.
    *list = head->next;

    // Return the value.
    int val = head->val;
    free(head);
    return val;
}


/* Adds a new element to the beginning of the list.
 *
 * list: pointer to pointer to Node
 * val: value to add
 */
void push(Node **list, int val) {
    // Make a new node pointing at the old head, and make it the new head
    Node *new_head = make_node(val, *list);
    *list = new_head;
}


/* Removes the first element with the given value
 *
 * Frees the removed node.
 *
 * list: pointer to pointer to Node
 * val: value to remove
 */
int remove_by_value(Node **list, int val) {
    Node *current = *list;

    // If only one element, if it matches, remove it, otherwise nothing happens
    if (current->next == NULL) {
        if (current->val == val) {
            *list = NULL;
        }
        return;
    }

    Node *prev = current;
    current = current->next;

    // Loop through next elements
    while (current != NULL) {
        // If the element matches, remove it by setting prev->next to the next item
        if (current->val == val) {
            prev->next = current->next;
            free(current);
            return;
        }

        prev = current;
        current = current->next;
    }
}


/* Reverses the elements of the list.
 *
 * Does not allocate or free nodes.
 *
 * list: pointer to pointer to Node
 */
void reverse(Node **list) {
    // Get first, set first->next = NULL
    Node *prev = *list;
    if (prev == NULL) {
        return;
    }
    Node *current = prev->next;
    prev->next = NULL;

    // Iterating, setting next->next = current;
    while (current != NULL) {
        // Get next to iterate to
        Node *next = current->next;

        // Reverse order of the pointing
        current->next = prev;

        // Update values
        prev = current;
        current = next;
    }

    *list = prev;
}


int main() {
    Node *head = make_node(1, NULL);
    head->next = make_node(2, NULL);
    head->next->next = make_node(3, NULL);
    head->next->next->next = make_node(4, NULL);

    Node **list = &head;
    print_list(list);

    int retval = pop(list);
    print_list(list);

    push(list, retval+10);
    print_list(list);

    remove_by_value(list, 3);
    print_list(list);

    remove_by_value(list, 7);
    print_list(list);

    reverse(list);
    print_list(list);
}
