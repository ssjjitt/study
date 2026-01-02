#pragma once
#include <iostream>
#include <windows.h>
#include <fstream>

using namespace std;

struct Stack {
	int number;
	Stack* head;
	Stack* next;
};

void menu();
void push(struct Stack*& MyStack);
void clearStack(struct Stack*& MyStack);
void showStack(Stack*& MyStack);
void clearStack(Stack*& MyStack);
void find(Stack* MySt1, Stack* MySt2, Stack* MySt3);
void WriteInFile(Stack* MySt, string fileName);
void ReadFromFile(Stack* MySt, string fileName);
