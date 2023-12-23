//
// Created by shark on 19.11.2023.
//

#include <string>
#include <vector>
using namespace std;

#ifndef TASK1_BITARRAY_H
#define TASK1_BITARRAY_H


class BitArray {
private:
    std::vector< unsigned int> array;
    unsigned int numOfBits = 0;

    class Reference{
    private:
        BitArray& bitArray;
        unsigned int ind;
    public:
        Reference(BitArray& BitArray, unsigned int index);
        Reference& operator=(bool value);
        explicit operator bool();
    };
public:
    BitArray() = default;
    ~BitArray() = default;

    //Конструирует массив, хранящий заданное количество бит.
    //Первые sizeof(unsigned long) бит можно инициализровать с помощью параметра value.
    explicit BitArray(unsigned int num_bits,  unsigned long value = 0);
    BitArray(const BitArray& b);


    //Обменивает значения двух битовых массивов.
    void swap(BitArray& b);

    BitArray& operator=(const BitArray& b);


    //Изменяет размер массива. В случае расширения, новые элементы
    //инициализируются значением value.
    void resize( unsigned int num_bits, bool value = false);
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
    BitArray& operator<<=(unsigned int n);
    BitArray& operator>>=(unsigned int n);
    BitArray operator<<(unsigned int n) const;
    BitArray operator>>(unsigned int n) const;


    //Устанавливает бит с индексом n в значение val.
    void set(unsigned int n, bool val = true);
    //Заполняет массив истиной.
    BitArray& set();

    //Устанавливает бит с индексом n в значение false.
    void reset(unsigned int n);
    //Заполняет массив ложью.
    BitArray& reset();

    bool getBit(unsigned int ind) const;

    //true, если массив содержит истинный бит.
    bool any() const;
    //true, если все биты массива ложны.
    bool none() const;
    //Битовая инверсия
    BitArray operator~() const;
    //Подсчитывает количество единичных бит.
    unsigned int count() const;


    //Возвращает значение бита по индексу i.
    BitArray::Reference operator[]( unsigned int i) ;


    unsigned int size() const;
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
