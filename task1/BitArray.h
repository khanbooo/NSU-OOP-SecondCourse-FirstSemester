//
// Created by shark on 19.11.2023.
//

#include <string>
#include <vector>
#include "BitArrayException.cpp"

using namespace std;

#ifndef TASK1_BITARRAY_H
#define TASK1_BITARRAY_H


class BitArray {
private:
    vector<unsigned long long> array;
    unsigned int numOfBits = 0;

    class Reference {
    private:
        BitArray& bitArray;
        unsigned int index;

    public:
        Reference(BitArray &bitArray, unsigned int i);
        Reference& operator=(bool value);
        Reference& operator=(Reference const& reference);
        explicit operator bool();
    };

    //Устанавливает бит с индексом n в значение val.
    void set(int i);

    //Устанавливает бит с индексом n в значение false.
    void reset(int i);

    bool read(int i) const;
public:
    BitArray() = default;
    ~BitArray() = default;

    //Конструирует массив, хранящий заданное количество бит.
    //Первые sizeof(unsigned long) бит можно инициализровать с помощью параметра value.
    explicit BitArray(int numBits, unsigned long long value = 0);

    // Конструктор копирования
    BitArray(const BitArray& b);

    //Обменивает значения двух битовых массивов.
    void swap(BitArray& b);

    // Присваивает значения одного массива другому
    BitArray& operator=(const BitArray& b);

    //Изменяет размер массива. В случае расширения, новые элементы
    //инициализируются значением value.
    void resize(int numBits, bool value = false);

    //Очищает массив.
    void clear();

    //Добавляет новый бит в конец массива. В случае необходимости
    //происходит перераспределение памяти.
    void push_back(bool bit);

    //Битовые операции над массивами.
    //Работают только на массивах одинакового размера.
    //Обоснование реакции на параметр неверного размера входит в задачу.
    BitArray& operator&=(const BitArray& b);
    BitArray& operator|=(const BitArray& b);
    BitArray& operator^=(const BitArray& b);

    //Битовый сдвиг с заполнением нулями.
    BitArray& operator<<=(int n);
    BitArray& operator>>=(int n);
    BitArray operator<<(int n) const;
    BitArray operator>>(int n) const;

    //Заполняет массив истиной.
    BitArray& set();

    //Заполняет массив ложью.
    BitArray& reset();

    //true, если массив содержит истинный бит.
    bool any() const;

    //true, если все биты массива ложны.
    bool none() const;

    //Битовая инверсия
    BitArray operator~() const;

    //Подсчитывает количество единичных бит.
    unsigned int count() const;

    //Возвращает значение бита по индексу i.
    bool operator[](unsigned int i) const;

    Reference operator[](unsigned int i) ;

    // Возвращает размер массива
    unsigned int size() const;

    // true, если размер массива 0, false иначе
    bool empty() const;

    //Возвращает строковое представление массива.
    string to_string();

    friend bool operator==(const BitArray & a, const BitArray & b);
    friend bool operator!=(const BitArray & a, const BitArray & b);

    friend BitArray operator&(const BitArray& b1, const BitArray& b2);
    friend BitArray operator|(const BitArray& b1, const BitArray& b2);
    friend BitArray operator^(const BitArray& b1, const BitArray& b2);
};




#endif //TASK1_BITARRAY_H
