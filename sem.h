//Omer Abdelsalam && Sai Madhuri Molleti
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "threads.h"
#define _GNU_SOURCE

struct Semaphore {
	int v;
	Queue* TCBQ;
};

void InitSem(struct Semaphore* s, int value) {
	if (value >= 0) {
		s->TCBQ = (Queue*)malloc(sizeof(Queue));
		s->v = value;
		InitQueue(s->TCBQ);
	}
	else {
		printf("Semaphore cannot be initialized to a negative number.\n");
	}
}

void P(struct Semaphore* s) {
	s->v--;
	TCB_t* temp = NewItem();
	if (s->v < 0) {
		temp = DelQueue(RunQ);
		AddQueue(s->TCBQ, temp);
		swapcontext(&(temp->context), &(RunQ->h->context));
	}
}

void V(struct Semaphore* s) {
	s->v++;
	TCB_t* temp = NewItem();
	if (s->v <= 0) {
		temp = DelQueue(s->TCBQ);
		AddQueue(RunQ, temp);
	}
	yield();
}

