// Преобразование двоичного дерева поиска в минимальную кучу
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <utility>
#include <iomanip>
using namespace std;

// Структура данных для хранения узла бинарного дерева
struct Node
{
    int data;
    Node* left = nullptr, * right = nullptr;

    Node() {}
    Node(int data) : data(data) {}
};

// Рекурсивная функция для вставки ключа в BST
Node* insert(Node* root, int key)
{
    // если корень нулевой, создаем новый узел и возвращаем его
    if (root == nullptr) {
        return new Node(key);
    }

    // если заданный ключ меньше корневого узла, повторить для левого поддерева
    if (key < root->data) {
        root->left = insert(root->left, key);
    }

    // если данный ключ больше, чем корневой узел, повторить для правого поддерева
    else {
        root->right = insert(root->right, key);
    }

    return root;
}

// Вспомогательная функция для обхода бинарного дерева по порядку уровней
void printLevelOrderTraversal(Node* root)
{
    int probel = 20;
    std::cout << '\n';
    // базовый случай: пустое дерево
    if (root == nullptr) {
        return;
    }

    queue<Node*> q;
    q.push(root);

    while (!q.empty())
    {

        int n = q.size();
        while (n--)
        {
            std::cout << std::setw(probel + 10) << std::setfill(' ');
            Node* front = q.front();
            q.pop();

            cout << front->data << ' ';

            if (front->left) {

                q.push(front->left);
            }

            if (front->right) {

                q.push(front->right);
            }
            probel /= 2;
        }
        cout << endl;
    }
}

// Функция для выполнения неупорядоченного обхода заданного бинарного дерева и
// поставить в queue все узлы (в порядке их появления)
void inorder(Node* root, queue<int>& keys)
{
    if (root == nullptr) {
        return;
    }

    inorder(root->left, keys);
    keys.push(root->data);
    inorder(root->right, keys);
}

// Функция для обхода заданного бинарного дерева в прямом порядке.
// Назначаем каждому встреченному узлу следующий ключ из queue
void preorder(Node* root, queue<int>& keys)
{
    // базовый случай: пустое дерево
    if (root == nullptr) {
        return;
    }

    // заменяем значение корневого ключа на следующий ключ из queue
    root->data = keys.front();
    keys.pop();

    // обрабатываем левое поддерево
    preorder(root->left, keys);

    // обрабатываем правое поддерево
    preorder(root->right, keys);
}

// Функция для преобразования BST в минимальную кучу
void convert(Node* root)
{
    // базовый вариант
    if (root == nullptr) {
        return;
    }

    // поддерживаем queue для хранения неупорядоченного обхода дерева
    queue<int> keys;

    // заполняем queue по порядку
    inorder(root, keys);

    // обход дерева в прямом порядке и для каждого встреченного узла
    // извлекаем ключ из очереди и назначаем его узлу
    preorder(root, keys);
}

int main()
{
    setlocale(LC_ALL, "rus");
    vector<int> keys = { 15, 18, 9, 10, 8, 19, 17 };    // вектор со значениями, которые будут образующими для дерева и кучи

    cout << "Преобразование дерева со значениями: ";
    Node* root = nullptr;
    for (int key : keys) {
        cout << key << " ";
        root = insert(root, key);
    }

    convert(root);
    printLevelOrderTraversal(root);

    return 0;
}