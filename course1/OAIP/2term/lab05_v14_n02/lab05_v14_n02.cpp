//Государство.Наименование, столица, численность населения, площадь, фамилия президента.
//Выбор государства по названию.
#include <iostream>
#include <windows.h>
#include <fstream>
using namespace std;
union Buf//объединение. 1 книжка
{
	char name[20], capital[20];
	float population, square;
	char president_surname[10];
};
struct Country
{
	char name[20], capital[20];
	float population, square;
	char president_surname[10];
};
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	Country mass[20];//основная структура, 20 стран
	Buf buf;//временная
	const char* file = "Country.bin";//ссылка, потому что константная, хранит название файла
	int i = 0, beg;
	char str[20];//строчка
	cout << "Введите информацию о 3 странах" << endl << endl;
	for (i = 0; i < 3; i++) {
		fstream in_out(file, ios::binary | ios::in | ios::out | ios::trunc);
		in_out.seekp(0);
		cout << "Введите наименование страны: ";
		beg = in_out.tellg();//указываем номер символа
		cin >> buf.name;
		in_out.write((char*)&buf.name, sizeof buf.name);//записываем в файл
		in_out.seekp(beg);
		in_out.read((char*)&mass[i].name, sizeof mass[i].name);//считываем из файла
		cout << "Введите столицу: ";
		beg = in_out.tellg();
		cin >> buf.capital;
		in_out.write((char*)&buf.capital, sizeof buf.capital);
		in_out.seekp(beg);
		in_out.read((char*)&mass[i].capital, sizeof mass[i].capital);
		cout << "Введите численность населения (в миллионах): ";
		beg = in_out.tellg();
		cin >> buf.population;
		in_out.write((char*)&buf.population, sizeof buf.population);
		in_out.seekp(beg);
		in_out.read((char*)&mass[i].population, sizeof mass[i].population);
		cout << "Введите площадь (в квадратных километрах): ";
		beg = in_out.tellg();
		cin >> buf.square;
		in_out.write((char*)&buf.square, sizeof buf.square);
		in_out.seekp(beg);
		in_out.read((char*)&mass[i].square, sizeof mass[i].square);
		cout << "Введите фамилию президента: ";
		beg = in_out.tellg();
		cin >> buf.president_surname;
		in_out.write((char*)&buf.president_surname, sizeof buf.president_surname);
		in_out.seekp(beg);
		in_out.read((char*)&mass[i].president_surname, sizeof mass[i].president_surname);
		in_out.close();
		cout << endl << endl;
	}
	cout << "Вывод информации о заданной стране" << endl;
	cout << "Введите название страны: ";
	cin >> str;
	cout << "Информация о данной стране:" << endl;
	for (i = 0; i < 3; i++) {
		if (strcmp(mass[i].name, str) == 0) {
			cout << "Столица: " << mass[i].capital << endl;
			cout << "Численность населения (в милионах): " << mass[i].population << endl;
			cout << "Площадь (в квадратных метрах): " << mass[i].square << endl;
			cout << "Фамилия президента: " << mass[i].president_surname << endl;
		}
		if (strcmp(mass[i].name, str) != 0 && i == 2) cout << "Информации о данной стране нет";
	}
}
