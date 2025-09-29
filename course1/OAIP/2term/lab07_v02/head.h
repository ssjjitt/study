#pragma once
#include <iostream>
#include <windows.h>
#include <fstream>

using namespace std;

// задаем наш стек
struct Stack {
	int number;
	Stack* head;
	Stack* next;
};

void menu();
void push(struct Stack*& MyStack); // функция для записи чисел
void showStack(Stack*& MyStack);// вывод на экран
void clearStack(Stack*& MyStack);// для очистки стека
void find(Stack* MySt1);// задание из варианта
void WriteInFile(Stack* MySt, string fileName);// запись в файл
void ReadFromFile(Stack* MySt, string fileName);// чтение из файла