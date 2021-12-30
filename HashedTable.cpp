#include "HashedTable.h"
#include <string.h>

CHashedTable::CHashedTable() : count(0), size(0), data(NULL) //обнуляем число элементов
{
    localadding = false;
}

CHashedTable::~CHashedTable()
{
    if (data!=NULL) delete [] data;
}

CHashedTable::CHashedTable (Elem* elem, int n) //конструктор из массива
{
    localadding = false;
    data = new Elem [n];
    count = size = n; //сохраняем количество
    for (int i = 0; i<n; i++) { //идём по элементам
        if (HasKey (elem[i].key)) continue;
        int j = Hash(elem[i].key); //получаем адрес
        if (data[j].occupied!=0) { //если уже занят
            for (int k = 1; k<count; k++) { //ищем новый адрес
                j = Hash(elem[i].key+k);
                if (data[j].occupied==0) break;
            }
        }
        if (data[j].occupied!=0) throw "Too many keys with one hash"; //все места заняты - ошибка
        data[j].occupied = 1; //записываем элемент, помечаем место занятым
        data[j].key = elem[i].key;
        data[j].info = new char [strlen(elem[i].info)+1];
        strcpy (data[j].info, elem[i].info);
    }
}

CHashedTable::CHashedTable (const CHashedTable &t) //конструктор копирования
{
    localadding = false;
    data = new Elem [t.size];
    count = t.count; //копируем всё из другого экземпляра
    size = t.size;
    for (int i = 0; i<size; i++) {
        data[i].key = t.data[i].key;
        data[i].occupied = t.data[i].occupied;
        data[i].info = new char [strlen(t.data[i].info)+1];
        strcpy (data[i].info, t.data[i].info);
    }
}

CHashedTable& CHashedTable::operator= (const CHashedTable t) //оператор присваивания
        {
    localadding = false;
    data = new Elem [t.size];
    count = t.count; //копируем всё из другого экземпляра
    size = t.size;
    for (int i = 0; i<size; i++) {
        data[i].key = t.data[i].key;
        data[i].occupied = t.data[i].occupied;
        data[i].info = new char [strlen(t.data[i].info)+1];
        strcpy (data[i].info, t.data[i].info);
    }
    return *this;
        }

        CHashedTable& CHashedTable::operator+= (const Elem& t)
                {
    int t1=-1, t2=-1;
    if (!localadding && size<count+1) Resize (count+1); //если это не перехеширование и памяти не хватает - выделяем
    int start, j, free = -1;
    start = j = Hash (t.key); //получаем адрес
    do {
        if (data[j].occupied==1 && data[j].key==t.key)
            return *this; //место занято и ключи совпадают,выходим
            if (data[j].occupied==-1)
                if(free == -1)
                    free = j;
                if (data[j].occupied == 0) {
                    if(free != -1)
                        j = free;
                    data[j].occupied = 1; //записываем новый элемент
                    data[j].key = t.key;
                    data[j].info = new char [strlen(t.info)+1];
                    strcpy (data[j].info, t.info);
                    if (!localadding) count++; //увеличиваем количество
                    return *this;
                }
                j = (j+step)%size;
    } while(start != j);
    if(free == -1)
        return *this;
    else
        j = free;
    data[j].occupied = 1; //записываем новый элемент
    data[j].key = t.key;
    data[j].info = new char [strlen(t.info)+1];
    strcpy (data[j].info, t.info);
    if (!localadding) count++; //увеличиваем количество
    return *this;
                }


                CHashedTable& CHashedTable::operator-= (const Elem& t)
                        {
    if (count == 0) return *this; //если таблица пуста, ничего не делаем
    int j = Hash (t.key); //получаем адрес
    if (data[j].occupied==0) return *this; //такого нет и не было
    if (data[j].occupied==-1 || data[j].key!=t.key) { //если место свободно или на нём другой элемент
        for (int k = 1; k<size; k++) { //перебираем другие адреса
            //j = Hash(t.key+k);
            j = (j+step)%size;
            if (data[j].occupied==1 && data[j].key==t.key) break; //если место занято и ключи совпадают, прерываем
        }
    }
    if (data[j].occupied==0 || data[j].key!=t.key) return *this; //не нашли - ничего не делаем
    data[j].occupied = -1; //условно удаляем
    count--; //уменьшаем количество
    return *this;
                        }

                        Elem CHashedTable::operator[] (int key)
                        {
    Elem null; //пустой элемент для возврата
    if (count == 0)
        return null; //если таблица пуста, возвращаем пустой
        int start, j;
        start = j = Hash (key); //ищем элемент аналогично прочим функциям
        if (data[j].occupied==0)
            return null; //такого нет и не было
            do {
                if (data[j].occupied == 1 && data[j].key==key)
                    return data[j];	//иначе возвращаем найденный
                    j = (j+step)%size;
            } while(j != start && data[j].occupied != 0);
            return null; //если не нашли, возвращаем пустой
                        }

                        bool CHashedTable::operator() (int key)
                        {
    if (count == 0)
        return false; //если таблица пуста, возвращаем пустой
        int start, j;
        start = j = Hash (key); //ищем элемент аналогично прочим функциям
        if (data[j].occupied==0)
            return false; //такого нет и не было
            do {
                if (data[j].occupied == 1 && data[j].key==key)
                    return true;	//иначе возвращаем найденный
                    j = (j+step)%size;
            } while(j != start && data[j].occupied != 0);
            return false; //если не нашли, возвращаем пустой
                        }

                        void CHashedTable::Clear ()
                        {
    if (count==0 || count==size) return; //если таблица пуста, нечего сжимать
    Elem* tmp = new Elem [count];
    int oldsize = size;
    size = count;
    for (int i = 0; i<oldsize; i++) { //идём по массиву
        if (data[i].occupied==0 || data[i].occupied==-1) continue; //если место свободно, пропускаем
        int j = Hash(data[i].key); //определяем "идеальный" адрес
        if (i==j) continue; //если элемент на нём и стоит, пропускаем
        for (int k = 0; k<size && j<i; k++) { //перебираем другие подходящие адреса, расположенные раньше текущего
            //j = (j+step)%size;j = Hash(data[i].key+k);
            j = (j+k)%size;
            if (data[j].occupied==0 || data[j].occupied==-1) break; //если нашли свободный, прерываем
        }
        if ((data[j].occupied==0 || data[j].occupied==-1) && j<i) { //если нашли свободный и он раньше текущего
            data[j] = data[i]; //кладём элемент на лучшую позицию
            data[i].occupied = -1; //старое место освобождаем
        }
    }
    for (int i=0; i<count; i++)
        tmp[i] = data[i];
    delete [] data;
    data = tmp;
                        }

                        unsigned int CHashedTable::Hash (int key)
                        {
    return key%size; //вычисляем адрес элемента как остаток от деления на максимальный размер таблицы
                        }

                        bool CHashedTable::HasKey (int key)
                        {
    for (int i = 0; i<size; i++)
        if (data[i].occupied!=0 && data[i].key == key) return true;
        return false;
                        }

                        void CHashedTable::Resize (int newsize) //перевыделение памяти и перехеширование
                        {
    localadding = true; //перехеширование
    Elem* tmp = data; //сохраняем указатель
    data = new Elem [newsize]; //выделяем новую память
    int oldsize = size; //сохраняем старый размер
    size = newsize; //пишем новый размер
    for (int i=0; i<oldsize; i++) //перехешируем с новым размером
        *this+=tmp[i];
    if (tmp!=NULL) delete [] tmp; //если указатель не пустой, освобождаем старую память
    localadding = false; //перехеширование закончили
                        }

                        ostream& operator << (ostream& str, CHashedTable& t) //вывод
                        {
    str << endl;
    for (int i=0; i<t.size; i++) { //выводим все элементы, кроме пустых и условно удалённых
        if (t.data[i].occupied == 0 || t.data[i].occupied == -1) continue;
        str << i << ": key = " << t.data[i].key << ", " << t.data[i].info << endl;
    }
    return str;
                        }

                        istream& operator >> (istream& str, CHashedTable& t) //ввод
                        {
    Elem tmp; //временная переменная для элемента
    cout << "Key: " << endl;
    str >> tmp.key; //ввод ключа
    cout << "Information: " << endl;
    tmp.info = new char [101];
    str >> tmp.info; //ввод информации
    t+=tmp; //добавление элемента
    return str;
                        }
