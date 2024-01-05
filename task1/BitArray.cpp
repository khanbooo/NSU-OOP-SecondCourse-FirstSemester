//
// Created by shark on 19.11.2023.
//

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include "BitArray.h"

#define SIZE_OF_BLOCK 64
#define MAX_BLOCK_VALUE 0xffffffffffffffff
using namespace std;

void BitArray::set(const int n) {
    if (n < 0) {
        throw BitArrayException("Index can't be negative.");
    }
    this->array[n / SIZE_OF_BLOCK] |= ((unsigned long long)1 << (SIZE_OF_BLOCK - 1 - n % SIZE_OF_BLOCK));
}

void BitArray::reset(const int n) {
    if (n < 0) {
        throw BitArrayException("Index can't be negative.");
    }
    this->array[n / SIZE_OF_BLOCK] &= ~((unsigned long long)1 << (SIZE_OF_BLOCK - 1 - n % SIZE_OF_BLOCK));
}

bool BitArray::read(const int n) const {
    if (n < 0) {
        throw BitArrayException("Index can't be negative.");
    }
    return this->array[n / SIZE_OF_BLOCK] >> (SIZE_OF_BLOCK - 1 - n % SIZE_OF_BLOCK) & 1;
}

BitArray::BitArray(int numBits, unsigned long long int value) {
    if (numBits < 0) {
        throw BitArrayException("Index can't be negative.");
    }
    if (value && numBits < SIZE_OF_BLOCK) {
        throw BitArrayException("Can't initialize first bits: bit array is too small.");
    }

    int size = (numBits - 1) / SIZE_OF_BLOCK + 1;
    numOfBits = size;
    array.resize(size);
    array[0] = value;
}

BitArray::BitArray(const BitArray &b) {
    array = b.array;
    numOfBits = b.numOfBits;
}

void BitArray::swap(BitArray &b) {
    BitArray c = *this;
    *this = b;
    b = c;
}

BitArray &BitArray::operator=(const BitArray &b) {
    array = b.array;
    numOfBits = b.numOfBits;
    return *this;
}

void BitArray::resize(int numBits, bool value) {
    if (numBits < 0) {
        throw BitArrayException("Index can't be negative.");
    }
    int newSize = (numBits - 1) % SIZE_OF_BLOCK + 1;
    if (value) {
        unsigned int internalShift = numOfBits % SIZE_OF_BLOCK;
        if (internalShift > 0) {
            array[array.size() - 1] |= MAX_BLOCK_VALUE >> internalShift;
        }
        array.resize(newSize, MAX_BLOCK_VALUE);
    }
    else {
        array.resize(newSize);
    }

    unsigned int externalShift = numBits % SIZE_OF_BLOCK;
    if (externalShift) {
        array[array.size() - 1] &= MAX_BLOCK_VALUE << (SIZE_OF_BLOCK - externalShift);
    }

    numOfBits = numBits;
}

void BitArray::clear() {
    array.clear();
    numOfBits = 0;
}

void BitArray::push_back(bool bit) {
    this->resize(numOfBits + 1, bit);
}

BitArray &BitArray::operator&=(const BitArray &b) {
    if (numOfBits != b.numOfBits){
        throw BitArrayException("The size of the arrays must be equal.");
    }
    for (int i = 0; i < array.size(); i++){
        array[i] &= b.array[i];
    }
    return *this;
}

BitArray &BitArray::operator|=(const BitArray &b) {
    if (numOfBits != b.numOfBits){
        throw BitArrayException("The size of the arrays must be equal.");
    }
    for (int i = 0; i < array.size(); i++){
        array[i] |= b.array[i];
    }
    return *this;
}

BitArray &BitArray::operator^=(const BitArray &b) {
    if (numOfBits != b.numOfBits){
        throw BitArrayException("The size of the arrays must be equal.");
    }
    for (int i = 0; i < array.size(); i++){
        array[i] ^= b.array[i];
    }
    return *this;
}

//
BitArray &BitArray::operator<<=(int n) {
    if (n < 0){
        throw BitArrayException("Index can't be negative.");
    }
    if (n >= numOfBits){
        this->reset();
        return *this;
    }

    int bigShift = n / SIZE_OF_BLOCK;
    int smallShift = n % SIZE_OF_BLOCK;
    if (bigShift > 0) {
        for (int i = 0; i < array.size() - bigShift; i++) {
            array[i] = array[i + bigShift];
        }
        for (int i = array.size() - bigShift; i < array.size(); i++) {
            array[i] = 0;
        }
    }
    if (smallShift > 0){
        for (int i = 0; i < array.size() - bigShift - 1; i++) {
            array[i] <<= smallShift;
            array[i] |= (array[i + 1] >> (SIZE_OF_BLOCK - smallShift));
        }

        array[array.size() - bigShift - 1] <<= smallShift;
    }

    return *this;
}

//
BitArray &BitArray::operator>>=(int n) {
    if (n < 0) {
        throw BitArrayException("Index can't be negative.");
    }
    if (n >= numOfBits) {
        this->reset();
        return *this;
    }

    int bigShift = n / SIZE_OF_BLOCK;
    int smallShift = n % SIZE_OF_BLOCK;
    if (bigShift > 0){
        for (int i = array.size() - 1; i >= bigShift; i--) {
            array[i] = array[i - bigShift];
        }
        for (int i = 0; i < bigShift; i++) {
            array[i] = 0;
        }
    }
    if (smallShift > 0){
        for (int i = array.size() - 1; i > bigShift; i--) {
            array[i] >>= smallShift;
            array[i] |= (array[i - 1] << (SIZE_OF_BLOCK - smallShift));
        }

        array[bigShift] >>= smallShift;

        unsigned int startShift = numOfBits % SIZE_OF_BLOCK;
        //
        if (startShift > 0){
            array[array.size() - 1] &= MAX_BLOCK_VALUE << (SIZE_OF_BLOCK - numOfBits % SIZE_OF_BLOCK);
        }
    }

    return *this;
}

BitArray BitArray::operator<<(int n) const {
    if (n < 0) {
        throw BitArrayException("Index can't be negative.");
    }
    BitArray shifted(*this);
    shifted <<= n;
    return shifted;
}

BitArray BitArray::operator>>(int n) const {
    if (n < 0) {
        throw BitArrayException("Index can't be negative.");
    }
    BitArray shifted(*this);
    shifted >>= n;
    return shifted;
}

BitArray &BitArray::set() {
    for (unsigned long long & i : array) {
        i = MAX_BLOCK_VALUE;
    }
    unsigned int startShift = numOfBits % SIZE_OF_BLOCK;
    if (startShift > 0) {
        array[array.size() - 1] &= MAX_BLOCK_VALUE << (SIZE_OF_BLOCK - numOfBits % SIZE_OF_BLOCK);
    }
    return *this;
}

BitArray &BitArray::reset() {
    for (unsigned long long & i : array) {
        i = 0;
    }
    return *this;
}

bool BitArray::any() const {
    return std::any_of(array.begin(), array.end(), [](unsigned long long a) {return a != 0;});
}

bool BitArray::none() const {
    return !std::any_of(array.begin(), array.end(), [](unsigned long long a) {return a != 0;});
}

BitArray BitArray::operator~() const {
    BitArray inverted(*this);
    for (unsigned long long &i : inverted.array) {
        i = ~i;
    }
    unsigned int startShift = numOfBits % MAX_BLOCK_VALUE;
    if (startShift > 0) {
        inverted.array[array.size() - 1] ^= MAX_BLOCK_VALUE >> (startShift);
    }
    return inverted;
}

unsigned int BitArray::count() const {
    unsigned int counter = 0;
    for (const unsigned long long& i: array) {
        counter += __builtin_popcountll(i);
    }
    return counter;
}

bool BitArray::operator[](unsigned int i) const {
    if (i > numOfBits) {
        return false;
    }
    return this->read(i);
}

BitArray::Reference BitArray::operator[](unsigned int i) {
    if (i >= numOfBits) {
        resize(i + 1);
    }

    return BitArray::Reference(*this, i);
}

unsigned int BitArray::size() const {
    return numOfBits;
}

bool BitArray::empty() const {
    return numOfBits == 0;
}

string BitArray::to_string() {
    string s;
    for (int i = 0; i < numOfBits; i++){
        s += (*this)[i]
             ? '1'
             : '0';
    }
    return s;
}

bool operator==(const BitArray &a, const BitArray &b) {
    if (a.numOfBits != b.numOfBits){
        return false;
    }
    return a.array == b.array;
}

bool operator!=(const BitArray &a, const BitArray &b) {
    if (a.numOfBits != b.numOfBits){
        return true;
    }
    return a.array != b.array;
}

BitArray operator&(const BitArray &b1, const BitArray &b2) {
    if (b1.size() != b2.size()){
        throw BitArrayException("The size of the arrays must be equal.");
    }
    BitArray result(b1);
    result &= b2;
    return result;
}

BitArray operator|(const BitArray &b1, const BitArray &b2) {
    if (b1.size() != b2.size()){
        throw BitArrayException("The size of the arrays must be equal.");
    }
    BitArray result(b1);
    result |= b2;
    return result;
}

BitArray operator^(const BitArray &b1, const BitArray &b2) {
    if (b1.size() != b2.size()){
        throw BitArrayException("The size of the arrays must be equal.");
    }
    BitArray result(b1);
    result ^= b2;
    return result;
}

BitArray::Reference::Reference(BitArray &bitArray, const unsigned int ind) : bitArray(bitArray) {
    this->bitArray = bitArray;
    this->index = ind;
}

BitArray::Reference &BitArray::Reference::operator=(const bool value) {
    if (value) {
        bitArray.set(index);
    }
    else {
        bitArray.reset(index);
    }
    return *this;
}

BitArray::Reference &BitArray::Reference::operator=(BitArray::Reference const& reference) {
    if (reference.bitArray.read(reference.index)) {
        bitArray.set(index);
    }
    else {
        bitArray.reset(index);
    }
    return *this;
}

BitArray::Reference::operator bool() {
    return bitArray.read(index);
}
