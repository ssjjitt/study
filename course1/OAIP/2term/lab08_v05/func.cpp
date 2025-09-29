#include "Header.h"

// �������� �������
void create(Number** begin, Number** end, int p) {
    Number* t = new Number;     // ��������� ������
    t->next = NULL;
    if (*begin == NULL)
        *begin = *end = t;
    else
    {
        t->info = p;    // ���������� ����
        (*end)->next = t;       // ������
        *end = t;
    }
}


// ��� ������ �������
void view(Number* begin)
{
    Number* t = begin;      // �������� ����� ��������
    if (t == NULL)
    {
        cout << "�����\n";
    }
    else {
        cout << "�������:\n";
        while (t != NULL)       // ���� ������� �� �����
        {
            cout << t->info << endl;    // ������� �������
            t = t->next;            // � �� ���������
        }
        cout << '\n';
    }
}

// ��� �������� �������
void del(Number* begin)
{
    Number* t = begin;      // �������� ������ ��������
    if (t == NULL)
    {
        cout << "�����\n";
    }
    else
    {
        while (t != NULL)
        {
            t->info = NULL;     // ������������� � ����
            t = t->next;            // � �� ���������
        }
    }
    cout << "�������� �������\n\n";
}

void delEl(Number* begin)
{
    Number* t = begin;      // �������� ������ ��������
    if (t == NULL)
    {
        cout << "�����\n";
    }
    else
    {
        t->info = NULL;     // ������������� � ����
    }
}

// ������ ������ �������
short sizeQ(Number* begin)
{
    Number* t = begin;      // �������� ������ ��������
    short counter = 0, data = t->info;
    while (t != NULL)
    {
        if (data != NULL)
        {
            counter++;      // ������� �������������
            t = t->next;    // ������������ ������
        }
        else t = t->next;
    }
    cout << "������ ������� = " << counter << "\n\n";
    return counter;
}


