#include "Header.h"
int sum = 0;

void Tree::AddNode(int k)		// фунцкия для добавления узла
{


	if (this->node == NULL)		// если узла нет, то есть он равен NULL
	{
		this->node = new Node;	// выделяем память
		this->node->count = 1;
		this->node->key = k;	// присваиваем значение
		this->node->left = this->node->right = NULL;	// очищаем память для след роста
		return;
	}

	Node* temp = this->node;

	while (true)
	{

		if (k == temp->key) // если k = одному из ключей
		{
			temp->count++;
			return;
		}

		if (k < temp->key)		// для левого поддерева
		{
			if (temp->left == NULL)
			{
				temp->left = new Node;
				temp->left->count = 1;
				temp->left->key = k;
				temp->left->left = temp->left->right = NULL;
				return;
			}
			else
			{
				temp = temp->left;
				continue;
			}

		}

		if (k > temp->key)		// для правого поддерева
		{
			if (temp->right == NULL)
			{
				temp->right = new Node;
				temp->right->count = 1;
				temp->right->key = k;
				temp->right->left = temp->right->right = NULL;
				return;
			}
			else
			{
				temp = temp->right;
				continue;
			}

		}
	}
}
void pushFromFile(Node** t, int a) {
	if ((*t) == NULL) {	// если дерева не существует
		(*t) = new Node;	// выделение памяти
		(*t)->key = a;	// присваиваем
		(*t)->left = (*t)->right = NULL;	// очищаем память для след роста
		return;
	}
	if (a > (*t)->key)	// если а > чем текущий элемент, то
		pushFromFile(&(*t)->right, a);		// направо
	else                                // иначе
		pushFromFile(&(*t)->left, a);	// налево
}

void Tree::PrintTree(Node* temp, int tab)
{
	int i;
	if (temp != NULL)		// если дерево не пустое
	{
		PrintTree(temp->right, tab + 1);	// рекурсия для правого поддерева
		for (i = 1; i <= tab; i++)
			cout << "   ";
		cout << temp->key << endl;		// печатаем
		PrintTree(temp->left, tab + 1);		// рекурсия для левого поддерева
	}
}
void Tree::Delete(int key)
{
	Node* Del, * Prev_Del, * R, * Prev_R;
	Del = this->node;
	Prev_Del = NULL;
	while (Del != NULL && Del->key != key)
	{
		Prev_Del = Del;
		if (Del->key > key)
			Del = Del->left;
		else
			Del = Del->right;
	}
	if (Del == NULL)
	{
		puts("\nНе найден");
	}
	if (Del->right == NULL)
		R = Del->left;
	else
		if (Del->left == NULL)
			R = Del->right;
		else
		{
			Prev_R = Del;
			R = Del->left;
			while (R->right != NULL)
			{
				Prev_R = R;
				R = R->right;
			}
			if (Prev_R == Del)
				R->right = Del->right;
			else
			{
				R->right = Del->right;
				Prev_R->right = R->left;
				R->left = Prev_R;
			}
		}
	if (Del == this->node) this->node = R;
	else
		if (Del->key < Prev_Del->key)
			Prev_Del->left = R;
		else
			Prev_Del->right = R;
	int tmp = Del->key;
	cout << "\nБыл удален элемент с ключом " << tmp << endl;
	delete Del;
}

// Функция печатает значения бинарного дерева поиска в прямом порядке.
// Вместо печати первой инструкцией функции может быть любое действие
// с данным узлом
void Tree::DirectBypass(Node* temp)
{
	if (temp)
	{
		cout << temp->key << "  ";
		if (temp->left)
			DirectBypass(temp->left);	// рекурсивный вызов для левого
		if (temp->right)
			DirectBypass(temp->right);	// рекурсивный вызов для правого
	}
}

// Функция печатает значения бинарного дерева поиска в симметричном порядке.
// То есть в отсортированном порядке
void Tree::ReverseBypass(Node* temp)
{
	if (temp)
	{
		if (temp->left)
			ReverseBypass(temp->left);
		cout << temp->key << "  ";
		if (temp->right)
			ReverseBypass(temp->right);
	}
}

// Функция печатает значения бинарного дерева поиска в обратном порядке.
// Не путайте обратный и обратноотсортированный (обратный симметричный).
void Tree::DownScan(Node* temp)
{
	if (temp != NULL)
	{
		DownScan(temp->left);
		DownScan(temp->right);
		cout << temp->key << "  ";
	}

}


bool Tree::Balance(Node* temp)
{
	if (temp)
	{
		if (temp->right)
		{
			this->counter++;
			Balance(temp->right);
		}

		if (temp->left)
		{
			this->counter--;
			Balance(temp->left);
		}
		if (this->counter >= -1 && this->counter <= 1)
			return true;
		else
			return false;
	}
}

int Tree::check_right(Node* temp)	// правые дочерние узлы
{
	if (temp) {
		if (temp->left)
		{
			check_right(temp->left);
			sum++;
		}
		if (temp->right)
			check_right(temp->right);

		return sum;
	}
}