// 2. Дана строка, состоящая из групп нулей и единиц.Определить самую короткую группу.
#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
    char string[256], *pstring = string, ch, simvgrupp;
    int kolvo = 256, minkolvo = 0;
    cout << "строка:  ";
    cin >> string;
    ch = *pstring;
    do {
        pstring++;
        minkolvo++;
        if (ch != *pstring) {
            if (kolvo > minkolvo) {
                kolvo = minkolvo;
                simvgrupp = ch;
            }
            ch = *pstring;
            minkolvo = 0;
        }
    } while (*pstring != '\0');
    cout << "самая короткая группа: ";
    for (int i = 0; i < kolvo; i++) cout << simvgrupp;
    return 0;
}