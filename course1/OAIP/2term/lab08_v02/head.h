#pragma once
#include<iostream>
using namespace std;

struct Number
{
	int info;
	Number* next;
};

void create(Number** begin, Number** end, int p);
void view(Number* begin);
void del(Number* begin);
short sizeQ(Number* begin);
Number* task(Number* begin);