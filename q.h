// Omer Abdelsalam && Sai Madhuri Molleti
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "TCB.h"
#define _GNU_SOURCE

/*
struct TCB_t {
	int payload; // The element our TCB_t carries
	struct TCB_t* next;  // Pointer to next TCB_t struct
	struct TCB_t* prev; // Pointer to previous TCB_t struct
};
*/

typedef struct Queue {
	TCB_t* h;
}Queue;

struct Queue* RunQ;

struct TCB_t* NewItem() { // returns a pointer to a new q-element
	TCB_t* node = (struct TCB_t*)malloc(sizeof(struct TCB_t));
	node = NULL;
	return node;
}

void InitQueue(struct Queue* head) { // creates an empty TCB_t, pointed to by the variable head.
	head->h = NewItem();
	//RunQ= NULL;
	//*head = h;
}

void AddQueue(struct Queue* head, struct TCB_t* item) { // adds a TCB_t item, pointed to by “item”, to the TCB_t pointed to by head.
	//RunQ = head;
	if (head->h == NULL) {
		head->h = item;
		item->next = head->h;
		item->prev = head->h;
	}
	else {
		struct TCB_t* temp = NewItem();
		temp = head->h;
		while (temp->next != head->h) {
			temp = temp->next;   // last thing on list
		}
		temp->next = item;			// temp is the second to last element, item is the last element now
		temp->next->prev = temp;	// item's previous is temp
		head->h->prev = temp->next;		// head's previous is item.
		temp->next->next = head->h;		// item's next is head.
	}
}

struct TCB_t* DelQueue(struct Queue* head) { // deletes an item from head and returns a pointer to the deleted item. If this is the last element…
	struct TCB_t* temp = NewItem();
	//RunQ= head;
	if (head== NULL) {
		printf("TCB_t is empty. Can not remove anything.\n");
	}
	else if (head->h->next == head->h) {
		temp = head->h;
		head->h->next = NULL;
		head->h->prev = NULL;
		head->h = NULL;
	}
	else {
		temp = head->h;
		head->h->prev->next = head->h->next;
		head->h->next->prev = head->h->prev;
		head->h = head->h->next;
	}
	//head = RunQ;
	return temp;
}

void RotateQ(struct Queue* head) { // Moves the header pointer to the next element in the TCB_t.
	//RunQ= head;
	if (head->h == NULL) {
		printf("TCB_t is empty. Cannot rotate.\n");
	}
	else {
		head->h = head->h->next;
	}
}
