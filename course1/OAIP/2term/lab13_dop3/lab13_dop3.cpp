// представляет ли массив минимальную бинарную кучу
#include <iostream>
#include <vector>
using namespace std;

// Функция для проверки, представляет ли данный массив минимальную кучу или нет
bool checkMinHeap(vector<int> const A, int i)
{
    // если `i` является листовым узлом, вернуть true, так как каждый листовой узел является кучей
    if (2 * i + 2 > A.size()) {
        return true;
    }

    // если `i` является внутренним узлом

    // рекурсивно проверяем, является ли левый потомок кучей
    bool left = (A[i] <= A[2 * i + 1]) && checkMinHeap(A, 2 * i + 1);

    // рекурсивно проверяем, является ли правый потомок кучей (чтобы избежать вывода индекса массива
    // границ, сначала проверьте, существует ли правильный дочерний элемент или нет)
    bool right = (2 * i + 2 == A.size()) ||
        (A[i] <= A[2 * i + 2] && checkMinHeap(A, 2 * i + 2));

    // вернуть true, если и левый, и правый дочерние элементы являются кучами
    return left && right;
}

int main()
{
    setlocale(LC_ALL, "rus");

    vector<int> A = { 1, 2, 3, 4, 5, 6 };

    vector<int> A1 = { 6, 5, 4, 3, 2, 1 };
    // начинаем с индекса 0 (корень кучи)
    int index = 0;

    if (checkMinHeap(A, index)) {
        for (auto item : A) cout << item << " ";
        cout << "\nМассив представляет собой минимальную кучу\n";
    }
    else {
        for (auto item : A) cout << item << " ";
        cout << "\nМассив не представляет собой минимальную кучу\n";
    }

    if (checkMinHeap(A1, index)) {
        for (auto item : A1) cout << item << " ";
        cout << "\nМассив представляет собой минимальную кучу\n";
    }
    else {
        for (auto item : A1) cout << item << " ";
        cout << "\nМассив не представляет собой минимальную кучу\n";
    }

    return 0;
}