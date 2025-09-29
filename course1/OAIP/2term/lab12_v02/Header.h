#pragma once
#include <iostream>
using namespace std;

struct  Node
{
	int key; // ключ
	int count; // счетчик
	Node* left; // левый узел
	Node* right; // правый узел
};

struct Tree
{
	Node* node = nullptr;
	int counter;
	void AddNode(int k); // добавление элемента
	void PrintTree(Node* temp, int l); // вывод дерева
	void Delete(int k); // удаление узла
	bool Balance(Node* temp); // сбалансированность дерева
	void DirectBypass(Node* temp); // прямой обход
	void ReverseBypass(Node* temp); // смешанный обход
	void DownScan(Node* temp); // обратный обход
	int check_right(Node* temp); // правые дочерние узлы
};