//Omer Abdelsalam && Sai Madhuri Molleti
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define _GNU_SOURCE
#include "sem.h"

//void method1_1();
//void method1_2();
//void method2_1();
//void method2_2();
void parent();
void method3_1();
void method3_2();
void method3_3();
int globalint = 0;
int in = 0;
int out = 0;
int buffer[3];
struct Semaphore *s, *full, *empty;

int main(void) {
	RunQ = (Queue*)malloc(sizeof(Queue));
	s = (struct Semaphore*)malloc(sizeof(struct Semaphore));
	full = (struct Semaphore*)malloc(sizeof(struct Semaphore));
	empty = (struct Semaphore*)malloc(sizeof(struct Semaphore));

	buffer[0] = 0;
	buffer[1] = 0;
	buffer[2] = 0;

	InitQueue(RunQ);
	InitSem(s, 1);
	InitSem(full, 3);
	InitSem(empty, 0);
	
	start_thread(method3_1);
	start_thread(method3_2);
	start_thread(method3_3);
	start_thread(parent);
	
	run();
}

/*
//Method1
void method1_1() {
	while (1) {
		P(s);
		printf("A\n");
		V(s);
	}
}

void method1_2() {
	while (1) {
		P(s);
		printf("B\n");
		V(s);
	}
}

//Method2
void method2_1() { // producer
	while(1){
		P(full);
		printf("producer\n");
		buffer[in] = buffer[in]+1;
		in = (in+1) % 3; // n = 3
		V(empty);
	}
}

void method2_2() { // consumer
	int item;
	while(1){
		P(empty);
		printf("consumer\n");
		item = buffer[out];
		out = (out + 1) % 3; // n = 3
		V(full);
		printf("item: %d\n", item);
	}
}
*/

void parent(){
	while(1){
		P(empty);
		for(int i = 0; i<3; i++){
			printf("item: %d\n", buffer[i]);
		}
		V(full);
	}
}

void method3_1() {
	while(1){
		P(full);
		P(s);
		buffer[0]++;
		V(s);
		V(empty);
	}
}

void method3_2() { 
	while(1){
		P(full);
		P(s);
		buffer[1]++;
		V(s);
		V(empty);
	}
}

void method3_3() {
	while(1){
		P(full);
		P(s);
		buffer[2]++;
		V(s);
		V(empty);
	}
}

