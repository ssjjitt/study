#include "head.h"

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
			if (el->number > 0)		// если > 0, перемещаемся дальше
			{
				el= el->next;
			}
			if (el->number < 0)		// если < 0
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