// Omer Abdelsalam && Sai Madhuri Molleti
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "q.h"
#define _GNU_SOURCE

void start_thread(void (*function)(void))
{
	int* stack = (int*)malloc(8192);
	struct TCB_t* tcb = (struct TCB_t*)malloc(sizeof(struct TCB_t));
	size_t size = sizeof(stack) / sizeof(stack[0]) - 1;
	tcb->thread_id = 0;
	init_TCB(tcb, function, stack, 8192);
	AddQueue(RunQ, tcb);
}

void run() {
	struct TCB_t* Curr_Thread = (struct TCB_t*)malloc(sizeof(struct TCB_t));
	Curr_Thread = RunQ->h;
	ucontext_t parent;	// get a place to store the main context, for faking
	getcontext(&parent);
	swapcontext(&parent, &(Curr_Thread->context)); // start the first thread
}

void yield() {
	struct TCB_t* Prev_Thread = (struct TCB_t*)malloc(sizeof(struct TCB_t));
	struct TCB_t* Curr_Thread = (struct TCB_t*)malloc(sizeof(struct TCB_t));
	Prev_Thread = RunQ->h;
	RotateQ(RunQ);
	printf("Thread ID: %d \n", Prev_Thread->thread_id);
	Curr_Thread = RunQ->h;
	swapcontext(&(Prev_Thread->context), &(Curr_Thread->context));
}