    #include <stdlib.h>
    #include "HashedTable.h"

#include "HashedTable.cpp"
	CHashedTable c;

char menu ()
{
    system ("cls");
    cout << "1. Default (empty)\n";
    cout << "2. From massive\n";
    cout << "3. Input\n";
    cout << "4. Output\n";
    cout << "5. Search element\n";
    cout << "6. Search information\n";
    cout << "7. Add element\n";
    cout << "8. Delete element\n";
    cout << "9. Reorganize table\n";
    cout << "0. Exit\n";
    cout << "\nGo to ";
    char c;
    cin >> c;
    return c;
}

void p1 ()
{
    CHashedTable a;
    cout << "a=" << a << endl;
    cin.get();
}


void p2 ()
{
    Elem e [4];
    e[0].key = 102; e[0].info = new char [10]; strcpy (e[0].info, "first");
    e[1].key = 113; e[1].info = new char [10]; strcpy (e[1].info, "second");
    e[2].key = 345; e[2].info = new char [10]; strcpy (e[2].info, "third");
    e[3].key = 13;  e[3].info = new char [10]; strcpy (e[3].info, "fourth");

    CHashedTable b (e, 4);
    cout << "b=" << b << endl;
    cin.get();
}

void p3 ()
{
    cin >> c; //работа потокового ввода >>, с клавиатуры вводятся данные для нового элемента
    cout << "c=" << c << endl;
    cin.get();
}

void p4 ()
{
    cout << "c=" << c << endl; //выводим на экран, демонстрация работы оператора <<
    cin.get();
}

void p5 ()
{
    int k;
    cout << "Key: " << endl;
    cin >> k;
    if (c(k)==true) cout << "Element found" << endl;
    else cout << "Element not found" << endl;
    //cout << "c(key) = " << c(k) << endl; //работа оператора ()
    cin.get();
}

void p6 ()
{
    int k;
    cout << "Key: " << endl;
    cin >> k;
    cout << "c[key] = " << c[k].info << endl; //работа оператора []
    cin.get();;
}

void p7 ()
{
    Elem e;
    e.key = 102; e.info = new char [10]; strcpy (e.info, "first");
    c+=e; //добавляем в объект а элемент e[0]
    cout << "c+=e[0]" << c << endl; //выводим результат
    cin.get();
}

void p8 ()
{
    Elem e [1];
    cout << "Key: " << endl;
    cin >> e[0].key;
    c-=e[0]; //удаляем из объекта b элемент e[1]
    cout << "b-=e[0]" << c << endl; //выводим результат
    cin.get();
}

void p9 ()
{
    c.Clear(); //сжатие объекта b
    cout << "c.Clear=" << c << endl; //выводим результат
    cin.get();
}

int main(int argc, char* argv[])
{ //пример
    bool p = true;
    while (p) {
        try {
            char c = menu();
            switch (c) {
                case '1':
                    p1();
                    break;
                    case '2':
                        p2();
                        break;
                        case '3':
                            p3();
                            break;
                            case '4':
                                p4();
                                break;
                                case '5':
                                    p5();
                                    break;
                                    case '6':
                                        p6();
                                        break;
                                        case '7':
                                            p7();
                                            break;
                                            case '8':
                                                p8();
                                                break;
                                                case '9':
                                                    p9();
                                                    break;
                                                    case '0':
                                                        p = false;
                                                        break;
            }
        } catch (char* ex) {
            cout << ex;
        }
    }
    return 0;
}