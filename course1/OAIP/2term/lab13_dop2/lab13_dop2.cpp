// является ли бинарное дерево минимальной кучей или нет
#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

// Структура данных для хранения узла бинарного дерева
struct Node
{
    int data;
    Node* left, * right;
    Node(int data)
    {
        this->data = data;
        this->left = this->right = nullptr;
    }
};


// Функция для нахождения общего количества узлов в бинарном дереве
int size(Node* root)
{
    if (root == nullptr) {
        return 0;
    }

    return 1 + size(root->left) + size(root->right);
}

// Функция для проверки, является ли данное бинарное дерево полным бинарным деревом
// и каждый узел имеет более высокое значение, чем его родитель
bool isHeap(Node* root, int i, int n)
{
    // базовый вариант
    if (root == nullptr) {
        return true;
    }

    // неполное бинарное дерево: вне допустимого диапазона индекса
    if (i >= n) {
        return false;
    }

    // текущий узел имеет большее значение, чем его левый или правый потомок
    if ((root->left && root->left->data <= root->data) ||
        (root->right && root->right->data <= root->data)) {
        return false;
    }

    // проверка левого и правого поддерева
    return isHeap(root->left, 2 * i + 1, n) && isHeap(root->right, 2 * i + 2, n);
}

// Функция для проверки того, является ли заданное бинарное дерево минимальной кучей или нет
bool isHeap(Node* root)
{
    int i = 0;
    return isHeap(root, i, size(root));
}

int main()
{
    int data1, datastorage[7];
    setlocale(LC_ALL, "rus");
    cout << "Элементы для кучи: ";
    cin >> data1;
    datastorage[0] = data1;
    Node* root = new Node(data1);   // выделяем память под новые узлы
    cin >> data1;
    datastorage[1] = data1;
    root->left = new Node(data1);
    cin >> data1;
    datastorage[2] = data1;
    root->right = new Node(data1);
    cin >> data1;
    datastorage[3] = data1;
    root->left->left = new Node(data1);
    cin >> data1;
    datastorage[4] = data1;
    root->left->right = new Node(data1);
    cin >> data1;
    datastorage[5] = data1;
    root->right->left = new Node(data1);
    cin >> data1;
    datastorage[6] = data1;
    root->right->right = new Node(data1);

    cout << "дерево состоит из элементов: ";
    for (int i = 0; i < 7; i++) {
        cout << datastorage[i] << " ";
    }
    if (isHeap(root)) {
        cout << "\nбинарное дерево является минимальной кучей\n";
    }
    else {
        cout << "\nбинарное дерево минимальной кучей не является\n";
    }

    return 0;
}
