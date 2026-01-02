#include <iostream>
#include <windows.h>
using namespace std;
enum Faculty {//перечисление
	LF = 1, LID, FTOV, FHTiT, FPiM, IEF, FIT
};
struct Date//битовые поля
{
	unsigned short day : 5;       // 5 битов - 32 числа
	unsigned short month : 4;    // 4 бита - 16  
	unsigned short year : 11;   // 11 бит - 2048
};

struct Student
{
	char surname[20], name[20], patronymic[20];
	Date date;//сюда помещаем битовое поле
	char spec[10];
	int group;
	int faculty;
	float ave_mark;
};
int main() {

	setlocale(LC_ALL, "Russian");
	Student mass[20];//на 20 студентов
	cout << "Добро пожаловать в базу данных студентов!" << endl << endl;;
	cout << "Что вы хотите выполнить?" << endl;
	cout << "1. - Запись нового студента" << endl;
	cout << "2. - Поиск студента по среднему баллу" << endl;
	cout << "3. - Удаление студента" << endl;
	cout << "0. - Выход" << endl << endl;
	int a, kol = 4, flag = 0, i = 0;
	float mark;
	char buf[20];
	do {
		cout << "Введите номер операции: ";
		cin >> a;
		cout << endl;
		switch (a)
		{
		case 1: int z;
			char str[5];
			cout << "Фамилия: ";
			cin >> mass[i].surname;//обращаемся к переменной в структуре 
			cout << "Имя: ";
			cin >> mass[i].name;
			cout << "Отчество: ";
			cin >> mass[i].patronymic;
			cout << "День зачисления: ";
			cin >> z;
			mass[i].date.day = z;
			cout << "Месяц зачисления: ";
			cin >> z;
			mass[i].date.month = z;//переменной присвоили значение z
			cout << "Год зачисления: ";
			cin >> z;
			mass[i].date.year = z;
			cout << "Специальность: ";
			cin >> mass[i].spec;
			cout << "Группа: ";
			cin >> mass[i].group;
			cout << "Факультет: ";
			cin >> str;
			if (strcmp(str, "ЛФ") == 0) mass[i].faculty = LF;//если стр = лф и тд, то присваиваем значение как у нас перечисление вверху. если кол-во различных символов = 0, то присваивает значение.
			if (strcmp(str, "ЛИД") == 0) mass[i].faculty = LID;
			if (strcmp(str, "ФТОВ") == 0) mass[i].faculty = FTOV;
			if (strcmp(str, "ФХТиТ") == 0) mass[i].faculty = FHTiT;
			if (strcmp(str, "ФПиМ") == 0) mass[i].faculty = FPiM;
			if (strcmp(str, "ИЭФ") == 0) mass[i].faculty = IEF;
			if (strcmp(str, "ФИТ") == 0) mass[i].faculty = FIT;
			cout << "Средний балл: ";
			cin >> mass[i].ave_mark;
			cout << endl;
			i++;
			break;
		case 2: cout << "Факультеты: ЛФ - 1, ЛИД - 2, ФТОВ - 3, ФХТиТ - 4, ФПиМ - 5, ИЭФ - 6, ФИТ - 7" << endl;
			cout << "Введите средний балл: ";
			cin >> mark;
			cout << "Информация о найденном студенте: " << endl;
			for (int j = 0; j < i + 1; j++) {
				if (mark == mass[j].ave_mark) {
					cout << "Фамилия: " << mass[j].surname << endl;
					cout << "Имя: " << mass[j].name << endl;
					cout << "Отчество: " << mass[j].patronymic << endl;
					cout << "День зачисления: " << mass[j].date.day << endl;
					cout << "Месяц зачисления: " << mass[j].date.month << endl;
					cout << "Год зачисления: " << mass[j].date.year << endl;
					cout << "Специальность: " << mass[j].spec << endl;
					cout << "Группа: " << mass[j].group << endl;
					cout << "Факультет: " << mass[j].faculty;
				}
			}
			cout << endl << endl;
			break;
		case 3: cout << "Фамилии студентов: ";
			for (int j = 0; j < i; j++)
				cout << mass[j].surname << ' ';
			cout << endl;
			cout << "Введите фамилию студента, которого нужно удалить: ";
			cin >> buf;
			for (int j = 0; j < i + 1; j++) {// j - основной цикл, где перебираем всех студентов
				if (strcmp(buf, mass[j].surname) == 0) {
					for (int k = j; k < i; k++) {
						mass[k] = mass[k + 1];
					}
					j--;//на шаг назад
					i--;//кол-во студентов
				}
			}
			cout << "Информация о заданном студенте удалена" << endl << endl;
			break;
		default: if (a != 0)
			cout << "Неверный номер операции, повторите попытку." << endl << endl; break;
		}
	} while (a != 0);
	cout << "До свидания!" << endl;
}
