#include "Header.h"
#include <fstream>
void main()
{
	int countChet = 0;
	setlocale(LC_ALL, "Russian");
	Tree* mainRoot = new Tree;
	int choice;

	// 13 8 17 4 11 15 25 2 6 22 27 20 33 
	while (1)
	{
		int numLeft = 1;
		cout << "\n";
		cout << "1 - Добавить элемент;\n";
		cout << "2 - Вывести дерево;\n";
		cout << "3 - Удалить элемент;\n";
		cout << "4 - Прямой обход с выводом;\n";
		cout << "5 - Обратный обход с выводом;\n";
		cout << "6 - Cмешанный обход с выводом;\n";
		cout << "7 - Балансировка дерева;\n";
		cout << "8 - Задание из 11 лаб 5 вар;\n";
		cout << "0 - Выход\n";
		cout << "Выберите:\n";
		cin >> choice;
		cout << "\n";

		switch (choice)
		{
		case 1:
		{
			cout << "\nДля остановки введите отрицательное число." << endl;
			cout << "Введите элемент: "; cin >> choice;
			while (choice > 0)
			{
				mainRoot->AddNode(choice);
				cout << "Введите элемент: "; cin >> choice;
				if (choice % 2 == 0)
				{
					countChet++;
				}
			}
			break;
		}

		case 2:
		{
			if (!mainRoot->node) cout << "В дереве ничего нет.\n";
			else mainRoot->PrintTree(mainRoot->node, 0);
			break;
		}

		case 3:
		{
			int key;
			cout << "Введите ключ элемента, который хотите удалить: "; cin >> key;
			mainRoot->Delete(key);
			break;
		}

		case 4:
		{
			if (!mainRoot->node) cout << "В дереве ничего нет.\n";
			else mainRoot->DirectBypass(mainRoot->node);
			break;
		}

		case 5:
		{
			if (!mainRoot->node) cout << "В дереве ничего нет.\n";
			else mainRoot->DownScan(mainRoot->node);
			break;
		}

		case 6:
		{
			if (!mainRoot->node) cout << "В дереве ничего нет.\n";
			else mainRoot->ReverseBypass(mainRoot->node);
			break;
		}

		case 7:
		{
			mainRoot->counter = 0;
			if (!mainRoot->node) cout << "В дереве ничего нет.\n";
			else
				if (mainRoot->Balance(mainRoot->node))
					cout << "Дерево сбалансировано." << endl;
				else
					cout << "Дерево не сбалансировано." << endl;
			break;
		}

		case 8:
		{
			numLeft = mainRoot->check_right(mainRoot->node);
			cout << "Количество правых дочерних вершин = " << numLeft << endl;
			break;
		}

		case 0:
		{
			exit(0);
			break;
		}

		default:
		{
			cout << "Такого пункта нет. Выберите снова.\n";
			break;
		}
		}
	}
}
