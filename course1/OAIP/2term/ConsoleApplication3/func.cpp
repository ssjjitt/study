#include "Header.h"

void push(struct Stack*& MyStack) {
	char chislo[9];
	cout << "Элементы: ";
	while (cin >> chislo && *chislo != 'q') {
		Stack* data = new Stack;
		data->number = atoi(chislo);
		data->next = MyStack->head;
		MyStack->head = data;
	}
	return;
}

void clearStack(Stack*& MyStack) {
	if (!MyStack->head) { cout << "Пусто!\n"; }
	else {
		while (MyStack->head) {
			Stack* delStack = MyStack->head;
			MyStack->head = MyStack->head->next;
			delete delStack;
		}
		cout << "Успешно!\n";
	}
}


void showStack(Stack*& MyStack) {
	Stack* data = MyStack->head;
	if (!MyStack->head) { cout << "Пусто\n"; }
	else { cout << "Элементы: \n"; }
	while (data) {
		cout << data->number << "\n";
		data = data->next;
	}
}

void find(Stack* MySt1, Stack* MySt2, Stack* MySt3) {
	if (!MySt1->head) { cout << "Пусто!\n"; }
	else if (!MySt2->head) { cout << "Пусто!\n"; }
	else {
		Stack* MyStack1 = new Stack;
		Stack* MyStack2 = new Stack;
		MyStack1->head = MySt1->head;
		MyStack2->head = MySt2->head;
		int b[20], a[20];
		int n = 0, r = 0;
		while (MyStack1->head) {
			a[n] = MyStack1->head->number;
			MyStack1->head = MyStack1->head->next;
			n++;
		}
		while (MyStack2->head) {
			b[r] = MyStack2->head->number;
			MyStack2->head = MyStack2->head->next;
			r++;
		}

		int c[20];
		int k = 0, l = 0;

		for (int i = 0; i < n; i++) {
			for(int j = 0; j < r; j++)
			if (a[i] == b[j]) {
				c[k] = a[i];
				k++;
			}
		}


		for (int i = 0; i < k; i++) {
			Stack* data = new Stack;
			data->number = c[i];
			data->next = MySt3->head;
			MySt3->head = data;
		}
	}
}

void WriteInFile(Stack* MySt, string fileName) {
	if (!MySt->head) { cout << "Пусто\n"; }
	else {
		ofstream FILE;
		FILE.open(fileName);
		Stack* MyStack = new Stack;
		MyStack->head = MySt->head;
		FILE << "Стек: ";
		while (MyStack->head) {
			FILE << "\n\t\t" << MyStack->head->number;
			MyStack->head = MyStack->head->next;
		}
		cout << "Записано в файл " << fileName << endl;

	}
}

void ReadFromFile(Stack* MySt, string fileName) {
	int indicate;
	ifstream FILE;
	FILE.open(fileName, ofstream::app);
	if (!(FILE >> indicate)) { cout << "Пусто!\n"; }
	else {
		while (indicate) {
			Stack* data = new Stack;
			data->number = indicate;
			data->next = MySt->head;
			MySt->head = data;
			if (!(FILE >> indicate)) { break; }
		}
		cout << "Прочитано!\n";
	}
	FILE.close();
}