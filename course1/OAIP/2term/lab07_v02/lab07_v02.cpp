#include "head.h"

void menu() {
	cout << "\n-----------------------------------------------------\n"
		 << "0) Выход\n"
		 << "1) Запись чисел в стек\n" 
		 << "2) Вывод стека\n"
		 << "3) Очистка стека\n"
		 << "4) Найти первый отрицательный элемент и удалить его\n"
		 << "5) Запись стека в файл\n"
		 << "6) Считать стек из файла\n"
		 << "\n-----------------------------------------------------\n"
		 << "Ваш выбор : ";
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int number, var;
	Stack* MyStack = new Stack;	// выделение памяти

	MyStack->head = nullptr;	

	while (true) {
		menu();
		cin >> var;
		switch (var) {
		case 0: return 0;
		case 1:
			cout << "Введите элементы первого стека:" << endl;
			push(MyStack);
			break;
		case 2:
			cout << "Элементы стека:" << endl;
			showStack(MyStack);
			break;
		case 3:
			clearStack(MyStack);
			break;
		case 4: find(MyStack);
			break;
		case 5:
			WriteInFile(MyStack, "text.txt");
			break;
		case 6:
			cout << "Элементы первого стека:" << endl;
			showStack(MyStack);
			break;
			break;
		}
	}
}