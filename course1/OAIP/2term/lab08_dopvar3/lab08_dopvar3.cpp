// Разработать функцию, которая удаляет первый положительный элемент, если такой есть.
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


void menu() {
	cout << "\n-----------------------------------------------------\n"
		<< "0) Выход\n"
		<< "1) Запись чисел в стек\n"
		<< "2) Вывод стека\n"
		<< "3) Очистка стека\n"
		<< "4) Найти первый положительный элемент и удалить его\n"
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

// функция для записи чисел
void push(struct Stack*& MyStack) {
	char chislo[9];		// символ, который будет вводится с клавиатуры
	while (cin >> chislo && *chislo != 'q') {		// пока не введем q
		Stack* data = new Stack;					//запрашиваем память под структуру для стека
		data->number = atoi(chislo);			// приведение строки в число
		data->next = MyStack->head;			// заполняем поля структуры
		MyStack->head = data;			// устанавливаем указатель на вершину стека
	}
	cout << "Элементы были успешно добавлены\n";
	return;
}

// для очистки стека
void clearStack(Stack*& MyStack) {
	if (!MyStack->head) { cout << "стек пуст\n"; }
	else {
		while (MyStack->head != NULL) {		// пока стек не пустой
			Stack* delStack = MyStack->head;	// хранение адреса элемента
			MyStack->head = MyStack->head->next;		// переход к следующему
			delete delStack;					// удаление элемента
		}
		cout << "стек пуст\n";
	}
}

// вывод на экран
void showStack(Stack*& MyStack) {
	Stack* data = MyStack->head;		// хранение адреса элемента
	if (!MyStack->head) { cout << "стек пуст\n"; }
	else {
		while (data) {
			cout << data->number << "\n";		// вывод
			data = data->next;		// переход к следующему
		}
	}
}

// задание из варианта
void find(Stack* MySt1) {
	if (!MySt1->head) { cout << "стек пуст\n"; }
	else {
		Stack* el = MySt1->head;		// хранение адреса элемента
		bool stop = true;
		while (stop)
		{
			if (el->number < 0)		// если < 0, перемещаемся дальше
			{
				el = el->next;
			}
			if (el->number > 0)		// если > 0
			{
				el->number = NULL;		// устанавливаем отрицательный элемент в ноль
				el = el->next;			// перемещаем дальше
				stop = false;
			}
		}
		showStack(MySt1);
	}
}

// запись в файл
void WriteInFile(Stack* MySt, string fileName) {
	if (!MySt->head) { cout << "стек пуст\n"; }
	else {
		ofstream FILE;					// открываем для записи
		FILE.open(fileName);
		Stack* MyStack = new Stack;			// выделение памяти
		MyStack->head = MySt->head;			// указатель на адрес элемента
		while (MyStack->head) {
			FILE << "\n\t\t" << MyStack->head->number;			// запись
			MyStack->head = MyStack->head->next;				// перемещение дальше
		}
		cout << "стек записан в " << fileName << endl;

	}
}

// чтение из файла
void ReadFromFile(Stack* MySt, string fileName) {
	int indicate;
	ifstream FILE;					// открываем для чтения
	FILE.open(fileName, ofstream::app);
	if (!(FILE >> indicate)) { cout << "ошибка чтения\n"; }
	else {
		while (indicate) {
			Stack* data = new Stack;		// выделение памяти
			data->number = indicate;
			data->next = MySt->head;
			MySt->head = data;
			if (!(FILE >> indicate)) { break; }
		}
		cout << "данные выведены\n";
	}
	FILE.close();
}