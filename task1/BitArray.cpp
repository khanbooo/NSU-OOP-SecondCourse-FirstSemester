//
// Created by shark on 19.11.2023.
//

#include <cstdlib>
#include <iostream>
#include <vector>
#include "BitArray.h"

#define SIZE_OF_BLOCK 32
#define MAX_BLOCK_VALUE 0xffffffff
using namespace std;

BitArray::BitArray(unsigned int num_bits,  unsigned long value) {
    if (num_bits < 0){
        throw BitArrayException("Number of bits can't be negative");
    }
    array.resize((num_bits - 1) / SIZE_OF_BLOCK + 1);
    numOfBits = num_bits;
    array[0] = value;
}

BitArray::BitArray(const BitArray &b) {
    array = b.array;
    numOfBits = b.numOfBits;
}

void BitArray::swap(BitArray &b) {
    BitArray tmp = *this;
    *this = b;
    b = tmp;
}

BitArray &BitArray::operator=(const BitArray &b) {
    array = b.array;
    numOfBits = b.numOfBits;
    return *this;
}

void BitArray::resize( unsigned int num_bits, bool value) {
    if (num_bits < 0){
        throw BitArrayException("Number of bits can't be negative");
    }

     unsigned int newNumOfBlocks = (num_bits - 1) / SIZE_OF_BLOCK + 1;
    if (value) {
        if (numOfBits % SIZE_OF_BLOCK != 0) {
            array[array.size() - 1] |= MAX_BLOCK_VALUE >> (numOfBits % SIZE_OF_BLOCK);
        }
        array.resize(newNumOfBlocks, MAX_BLOCK_VALUE);
    } else {
        array.resize(newNumOfBlocks, 0);
    }

    if (newNumOfBlocks % SIZE_OF_BLOCK != 0) {
        array[array.size() - 1] &= MAX_BLOCK_VALUE << (SIZE_OF_BLOCK - (numOfBits % SIZE_OF_BLOCK));
    }

    numOfBits = num_bits;
}

void BitArray::clear() {
    array.clear();
    numOfBits = 0;
}

void BitArray::push_back(bool bit) {
    resize(numOfBits + 1, bit);
}

BitArray &BitArray::operator&=(const BitArray &b) {
    if (numOfBits != b.size()){
        throw BitArrayException("BitArray operands must be of the same size");
    }
    for( unsigned int i = 0; i < array.size() - 1; i++){
        array[i] &= b.array[i];
    }
    return *this;
}

BitArray &BitArray::operator|=(const BitArray &b) {
    if (numOfBits != b.size()){
        throw BitArrayException("BitArray operands must be of the same size");
    }
    for( unsigned int i = 0; i < array.size() - 1; i++){
        array[i] |= b.array[i];
    }
    return *this;
}

BitArray &BitArray::operator^=(const BitArray &b) {
    if (numOfBits != b.size()){
        throw BitArrayException("BitArray operands must be of the same size");
    }
    for( unsigned int i = 0; i < array.size() - 1; i++){
        array[i] ^= b.array[i];
    }
    if (numOfBits % SIZE_OF_BLOCK != 0) {
        array[array.size() - 1] &= MAX_BLOCK_VALUE >> (SIZE_OF_BLOCK - (numOfBits % SIZE_OF_BLOCK));
    }
    return *this;
}

BitArray &BitArray::operator<<=(unsigned int n) {
    if (n < 0){
        throw BitArrayException("Number of bits can't be negative");
    }
    if (n >= numOfBits){
        this->reset();
        return *this;
    }

    unsigned int numOfResettedBlocks = n / SIZE_OF_BLOCK;
    if (numOfResettedBlocks > 0){
        for (unsigned int i = 0; i < array.size() - numOfResettedBlocks; i++){
            array[i] = array[i + numOfResettedBlocks];
        }
        for (unsigned int i = array.size() - numOfResettedBlocks; i < array.size(); i++){
            array[i] = 0;
        }
    }

    unsigned int restShift = n % SIZE_OF_BLOCK;
    if (restShift > 0){
        for (unsigned int i = 0; i < array.size() - numOfResettedBlocks - 1; i++){
            array[i] <<= restShift;
            array[i] |= array[i + 1] >> (SIZE_OF_BLOCK - restShift);
        }
        array[array.size() - numOfResettedBlocks - 1] <<= restShift;
    }

    return *this;
}

BitArray &BitArray::operator>>=(unsigned int n) {
    if (n < 0){
        throw BitArrayException("Number of bits can't be negative");
    }
    if (n >= numOfBits){
        this->reset();
        return *this;
    }

    unsigned int numOfResettedBlocks = n / SIZE_OF_BLOCK;
    if (numOfResettedBlocks > 0){
        for (unsigned int i = array.size() - 1; i >= numOfResettedBlocks; i--){
            array[i] = array[i - numOfResettedBlocks];
        }
        for (unsigned int i = 0; i < numOfResettedBlocks; i++){
            array[i] = 0;
        }
    }

    unsigned int restShift = n % SIZE_OF_BLOCK;
    if (restShift){
        for (unsigned int i = array.size() - 1; i > numOfResettedBlocks; i--){
            array[i] >>= restShift;
            array[i] |= (array[i - 1] << (SIZE_OF_BLOCK - restShift));
        }
        array[numOfResettedBlocks] >>= restShift;
        array[array.size() - 1] &= (MAX_BLOCK_VALUE >> (restShift));
    }

    return *this;
}

BitArray BitArray::operator<<(unsigned int n) const {
    if (n < 0){
        throw BitArrayException("Number of bits can't be negative");
    }
    BitArray shifted(*this);
    shifted <<= n;
    return shifted;
}

BitArray BitArray::operator>>(unsigned int n) const {
    if (n < 0){
        throw BitArrayException("Number of bits can't be negative");
    }
    BitArray shifted(*this);
    shifted >>= n;
    return shifted;
}

void BitArray::set(unsigned int n, bool val) {
    if (n < 0){
        throw BitArrayException("Number of bits can't be negative");
    }
    array[n / (SIZE_OF_BLOCK )] |= 1 << (SIZE_OF_BLOCK - n % SIZE_OF_BLOCK - 1);
}

BitArray &BitArray::set() {
    for (unsigned int i = 0; i < array.size() - 1; i++){
        array[i] = MAX_BLOCK_VALUE;
    }
    if (numOfBits % SIZE_OF_BLOCK != 0){
        array[array.size() - 1] = MAX_BLOCK_VALUE >> (SIZE_OF_BLOCK - numOfBits % SIZE_OF_BLOCK - 1);
    }
    return *this;
}

void BitArray::reset(unsigned int n) {
    if (n < 0){
        throw BitArrayException("Number of bits can't be negative");
    }
    array[n / (SIZE_OF_BLOCK )] &= ~(1 << (SIZE_OF_BLOCK - n % SIZE_OF_BLOCK));
}

BitArray &BitArray::reset() {
    for ( unsigned int i = 0; i < array.size() - 1; i++){
        array[i] = 0;
    }
    return *this;
}

bool BitArray::any() const {
    for (unsigned int i = 0; i < array.size() - 1; i++) {
        if (array[i]) {
            return true;
        }
    }
    return false;
}

bool BitArray::none() const {
    for (unsigned int i = 0; i < array.size() - 1; i++) {
        if (array[i]) {
            return false;
        }
    }
    return true;
}

BitArray BitArray::operator~() const {
    BitArray inverted(*this);
    for ( unsigned int i = 0; i < inverted.size() - 1; i++){
        inverted.array[i] = ~inverted.array[i];
    }
    if (inverted.numOfBits % SIZE_OF_BLOCK != 0){
        inverted.array[inverted.array.size() - 1] &=
                MAX_BLOCK_VALUE << (SIZE_OF_BLOCK - inverted.numOfBits % SIZE_OF_BLOCK);
    }
    return *this;
}

unsigned int BitArray::count() const {
    unsigned int counter = 0;
    for ( unsigned int i = 0; i < array.size() - 1; i++){
        counter += __builtin_popcountll(array[i]);
    }
    return counter;
}

BitArray::Reference BitArray::operator[](unsigned int i) {
    if (i < 0 ){
        throw Error("Index must be positive");
    }
    if (i > numOfBits) {
        this->resize(i + 1);
    }
    Reference reference(*this, i);
    return reference;
}

unsigned int BitArray::size() const {
    return numOfBits;
}

bool BitArray::empty() const {
    return numOfBits == 0;
}

string BitArray::to_string() {
    string str;
    for (unsigned int i = 0; i < numOfBits; i++){
        str += (*this)[i] ? '1' : '0';
    }
    return str;
}

bool operator==(const BitArray & a, const BitArray & b){
    return (a.numOfBits == b.numOfBits) && (a.array == b.array);
}

bool operator!=(const BitArray & a, const BitArray & b){
    return (a.numOfBits != b.numOfBits) || (a.array != b.array);
}

BitArray operator&(const BitArray& b1, const BitArray& b2){
    if (b1.numOfBits != b2.numOfBits){
        //tbd
    }
    BitArray bitArray(b1);
    bitArray &= b2;
    return bitArray;
}

BitArray operator|(const BitArray& b1, const BitArray& b2){
    if (b1.numOfBits != b2.numOfBits){
        throw BitArrayException("BitArray operands must be of the same size");
    }
    BitArray bitArray(b1);
    bitArray |= b2;
    return bitArray;
}

BitArray operator^(const BitArray& b1, const BitArray& b2){
    if (b1.numOfBits != b2.numOfBits){
        throw BitArrayException("BitArray operands must be of the same size");
    }
    BitArray bitArray(b1);
    bitArray ^= b2;
    return bitArray;
}

BitArray::Reference::Reference(BitArray &b, unsigned int index) : bitArray(b) {
    ind = index;
}

BitArray::Reference &BitArray::Reference::operator=(bool value) {
    if (value){
        bitArray.set(ind);
    }
    else{
        bitArray.reset(ind);
    }
    return *this;
}

bool BitArray::getBit(unsigned int ind) const{
    return ((array[ind / SIZE_OF_BLOCK]) >> (SIZE_OF_BLOCK - ind % SIZE_OF_BLOCK - 1)) & 1;
}

BitArray::Reference::operator bool() {
    return bitArray.getBit(ind);
}

int main(){
    BitArray bitArray(10);
    bitArray[5] = true;
    cout << bool(bitArray[5]) << ' ' << bitArray.to_string() << endl;
    bitArray[3] = true;
    cout << bool(bitArray[3]) << ' ' << bitArray.to_string() << endl;
    bitArray <<= 3;
    cout << bool(bitArray[3]) << ' ' << bitArray.to_string() << endl;
    bitArray[0] = true;
    cout << bool(bitArray[0]) << ' ' << bitArray.to_string() << endl;
}