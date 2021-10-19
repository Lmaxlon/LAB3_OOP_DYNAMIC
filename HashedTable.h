#pragma once
#include <iostream>
using namespace std;

struct Elem { //элемент таблицы
    int key; //ключ
    int occupied; //признак занятости
    char* info; //информация
    Elem () : key(0),occupied(0),info(NULL) {}; //конструктор по умолчанию
    ~Elem () { if (info!=NULL) delete [] info; } //деструктор для строки
    Elem (const Elem& el):key(el.key),occupied(el.occupied) { //конструктор копирования
        info = new char [strlen(el.info)+1]; strcpy (info, el.info);}
        Elem& operator = (const Elem el) { //оператор присваивания
        key=el.key; occupied = el.occupied;
        if (info!=NULL) delete [] info;
        info = new char [strlen(el.info)+1]; strcpy (info, el.info);
        return *this;
    }
};


class CHashedTable
        {
    static const int step = 1;
    unsigned int size; //количество элементов в таблице
    unsigned int count; //количество элементов в таблице
    Elem* data; //массив данных
    bool localadding; //флаг для перехеширования

        public:
            CHashedTable(); //конструктор по умолчанию
            CHashedTable (Elem* elem, int n); //конструктор из массива
            CHashedTable (const CHashedTable &t); //конструктор копирования
            ~CHashedTable(); //деструктор

            CHashedTable& operator= (const CHashedTable t); //оператор присваивания

            CHashedTable& operator+= (const Elem& t);
            CHashedTable& operator-= (const Elem& t);

            Elem operator[] (int key); //получение элемента по ключу
            bool operator() (int key); //проверка существования элемента по ключу

            void Clear (); //сжатие таблицы (условное, поскольку память статическая)

            friend ostream& operator << (ostream& str, CHashedTable& t); //вывод
            friend istream& operator >> (istream& str, CHashedTable& t); //ввод

        private:
            unsigned int Hash (int key); //функция хеширования
            bool HasKey (int key);
            void Resize (int newsize);
        };