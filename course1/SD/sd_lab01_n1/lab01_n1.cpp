#include <iostream>
using namespace std;
enum planets {// объявим наше перечисление
    mercury = 1,
    venus,
    earth,
    mars,
    jupiter,
    saturn,
    uran
};

int numInput(int num) {   // в случае ошибки ввода наша программа не будет останавливаться
    cin >> num;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nВы ввели не число, введите повторно!\n" << endl;
        numInput(num);
    }
    else return num;
}
int main()
{
    setlocale(LC_ALL, "rus");
    int number = 0;
    cout << "Какая по расположению планета от солнца?\n"
        << " 1 - меркурий,\n 2 - венера,\n 3 - земля,\n 4 - марс,\n 5 - юпитер,\n 6 - сатурн,\n 7 - уран\n 0 - выход\n";
    do {
        number = numInput(number);
        switch (number)
        {
        case planets::mercury:
            cout << "меркурий\n";
            break;
        case planets::venus:
            cout << "венера\n";
            break;
        case planets::earth:
            cout << "земля\n";
            break;
        case planets::mars:
            cout << "марс\n";
            break;
        case planets::jupiter:
            cout << "юпитер\n";
            break;
        case planets::saturn:
            cout << "сатурн\n";
            break;
        case planets::uran:
            cout << "уран\n";
            break;
        case 0:
            break;
        default:
            cout << "\nНеверное значение, введите повторно!\n";
            break;
        }
    } while (number != 0);
}
