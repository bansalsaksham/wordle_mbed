//=================================================================
// Implementation for DLL module.
//
// Copyright 2024 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//
// Name: Saksham Bansal
// GT ID: 903898700
//=================================================================
#include <stdlib.h>
#include <stdio.h>
#include "doubly_linked_list.h"

// Create a new LLNode with the given data
LLNode* create_llnode(void* data) {
    // Allocate memory for a new node
    LLNode* newNode = (LLNode*)malloc(sizeof(LLNode));
    if (newNode == NULL) {
        // Check for memory allocation failure
        printf("Memory allocation failed\n");
        return NULL;
    }
    // Initialize the node fields
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    
    return newNode; // Return the new node
}

// Create a new DLinkedList and initialize it
DLinkedList* create_dlinkedlist(void) {
    // Allocate memory for a new linked list
    DLinkedList* newList = (DLinkedList*)malloc(sizeof(DLinkedList));
    if (newList == NULL) {
        // Check for memory allocation failure
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    // Initialize the list fields
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    return newList;
}

// Get the size of the doubly linked list
int getSize(DLinkedList* dLinkedList) {
    // Return the size of the list
    return dLinkedList ? dLinkedList->size : 0;
}

// Get the head node of the list
LLNode* getHead(DLinkedList* dLinkedList) {
    // Return the head node of the list
    return dLinkedList ? dLinkedList->head : NULL;
}

// Get the tail node of the list
LLNode* getTail(DLinkedList* dLinkedList) {
    // Return the tail node of the list
    return dLinkedList ? dLinkedList->tail : NULL;
}

// Get the next node from the given node
LLNode* getNext(LLNode* node) {
    // Return the next node if it exists
    return (node != NULL) ? node->next : NULL;
}

// Get the previous node from the given node
LLNode* getPrev(LLNode* node) {
    // Return the previous node if it exists
    return (node != NULL) ? node->prev : NULL;
}

// Get the data from the given node
void* getData(LLNode* node) {
    // Return the data stored in the node
    return (node != NULL) ? node->data : NULL;
}

// Insert a node after a given node
void insertAfter(DLinkedList* dLinkedList, LLNode* prev_node, void* data) {
    if (!dLinkedList || prev_node == NULL) {
        // Check if the list or previous node is NULL
        fprintf(stderr, "The list or previous node cannot be NULL\n");
        return;
    }

    // Create a new node with the given data
    LLNode* newNode = create_llnode(data);
    if (newNode == NULL) return; // Check for allocation failure

    // Adjust pointers to insert the new node after prev_node
    newNode->next = prev_node->next;
    newNode->prev = prev_node;

    if (prev_node->next != NULL) {
        // Link the next node's previous pointer to the new node
        prev_node->next->prev = newNode;
    } else {
        // If prev_node was the tail, update the list's tail pointer
        dLinkedList->tail = newNode;
    }
    prev_node->next = newNode;
    dLinkedList->size++; // Increment the size
}

// Insert a node before a given node
void insertBefore(DLinkedList* dLinkedList, LLNode* next_node, void* data) {
    if (!dLinkedList || next_node == NULL) {
        // Check if the list or next node is NULL
        fprintf(stderr, "The list or next node cannot be NULL\n");
        return;
    }

    // Create a new node with the given data
    LLNode* newNode = create_llnode(data);
    if (newNode == NULL) return; // Check for allocation failure

    // Adjust pointers to insert the new node before next_node
    newNode->prev = next_node->prev;
    newNode->next = next_node;

    if (next_node->prev != NULL) {
        // Link the previous node's next pointer to the new node
        next_node->prev->next = newNode;
    } else {
        // If next_node was the head, update the list's head pointer
        dLinkedList->head = newNode;
    }
    next_node->prev = newNode;
    dLinkedList->size++; // Increment the size
}

// Insert a new node at the head of the list
void insertHead(DLinkedList* dLinkedList, void* data) {
    if (dLinkedList == NULL) return;

    if (dLinkedList->head == NULL) {
        // If the list is empty, create the first node
        LLNode* newNode = create_llnode(data);
        if (newNode == NULL) return; // Check for allocation failure
        dLinkedList->head = newNode;
        dLinkedList->tail = newNode;
        dLinkedList->size++;
    } else {
        // Call insertBefore to insert at the head
        insertBefore(dLinkedList, dLinkedList->head, data);
    }
}

// Insert a new node at the tail of the list
void insertTail(DLinkedList* dLinkedList, void* data) {
    if (dLinkedList == NULL) return;

    if (dLinkedList->tail == NULL) {
        // If the list is empty, create the first node
        LLNode* newNode = create_llnode(data);
        if (newNode == NULL) return; // Check for allocation failure
        dLinkedList->head = newNode;
        dLinkedList->tail = newNode;
        dLinkedList->size++;
    } else {
        // Call insertAfter to insert at the tail
        insertAfter(dLinkedList, dLinkedList->tail, data);
    }
}

// Delete a node from the list
void deleteNode(DLinkedList* dLinkedList, LLNode* node) {
    if (!dLinkedList || node == NULL || dLinkedList->size == 0) {
        // Check if node is NULL or list is empty
        return;
    }

    // Adjust pointers for node removal
    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        // Node is the head, update the head pointer
        dLinkedList->head = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    } else {
        // Node is the tail, update the tail pointer
        dLinkedList->tail = node->prev;
    }

    // Free the node and decrement the size
    free(node);
    dLinkedList->size--;
}

// Destroy the entire list and free memory
void destroyList(DLinkedList* dLinkedList) {
    if (dLinkedList == NULL) return;

    LLNode* current = dLinkedList->head;
    while (current != NULL) {
        LLNode* next = current->next;
        free(current);
        current = next;
    }
    free(dLinkedList);
    // No return statement needed as the function has a void return type
}

// Reverse the list in-place
void reverse(DLinkedList* dLinkedList) {
    if (!dLinkedList || dLinkedList->size <= 1) {
        // No need to reverse if the list has 0 or 1 element
        return;
    }

    LLNode* current = dLinkedList->head;
    LLNode* temp = NULL;
    
    while (current != NULL) {
        // Swap next and prev for each node
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    // Swap the head and tail pointers
    temp = dLinkedList->head;
    dLinkedList->head = dLinkedList->tail;
    dLinkedList->tail = temp;
}
