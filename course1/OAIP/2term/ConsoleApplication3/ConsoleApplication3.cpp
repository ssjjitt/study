#include "Header.h"

void menu() {
	cout << "0) Выход из приложения\n1) Запись чисел в стек\n" <<
		"2) Вывод стека\n3) Очистка стека\n4) Задание из вариант(СНАЧАЛА НАЖАТЬ СЮДА ПОТОМ ВЫВЕСТИ СТЕК, ИНАЧЕ НЕ СРАБОТАЕТ!!!)"
		<< "\n5) Запись стека в файл\n6)Считать стек из файла\nВаш выбор: ";
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int number, vibor;
	Stack* MyStack1 = new Stack;
	Stack* MyStack2 = new Stack;
	Stack* MyStack3 = new Stack;

	MyStack1->head = nullptr;
	MyStack2->head = nullptr;
	MyStack3->head = nullptr;

	while (true) {
		menu();
		cin >> vibor;
		switch (vibor) {
		case 0: return 0;
		case 1:
			cout << "\nДЛЯ ЗАВЕРШЕНИЯ ВВОДА ВВЕДИТЕ q\n";
			cout << "Введите элементы первого стека:" << endl;
			push(MyStack1);
			cout << "Введите элементы второго стека:" << endl;
			push(MyStack2);
			break;
		case 2:
			cout << "Элементы первого стека:" << endl;
			showStack(MyStack1);
			cout << "Элементы второго стека:" << endl;
			showStack(MyStack2);
			cout << "Элементы третьего стека:" << endl;
			showStack(MyStack3);
			break;
		case 3:
			clearStack(MyStack1);
			clearStack(MyStack2);
			clearStack(MyStack3);
			break;
		case 4: find(MyStack1, MyStack2, MyStack3);
			break;
		case 5:
			WriteInFile(MyStack1, "Data1.txt");
			WriteInFile(MyStack2, "Data2.txt");
			WriteInFile(MyStack3, "Data3.txt");
			break;
		case 6:
			cout << "Элементы первого стека:" << endl;
			showStack(MyStack1);
			cout << "Элементы второго стека:" << endl;
			showStack(MyStack2);
			cout << "Элементы третьего стека:" << endl;
			showStack(MyStack3);
			break;
			break;
		}
	}
}