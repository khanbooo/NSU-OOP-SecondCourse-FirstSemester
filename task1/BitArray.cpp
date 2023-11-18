//
// Created by shark on 19.11.2023.
//

#include "BitArray.h"

BitArray::BitArray() {

}

BitArray::~BitArray() {

}

BitArray::BitArray(int num_bits, unsigned long value) {

}

BitArray::BitArray(const BitArray &b) {

}

void BitArray::swap(BitArray &b) {

}

BitArray &BitArray::operator=(const BitArray &b) {
    return <#initializer#>;
}

void BitArray::resize(int num_bits, bool value) {

}

void BitArray::clear() {

}

void BitArray::push_back(bool bit) {

}

BitArray &BitArray::operator&=(const BitArray &b) {
    return <#initializer#>;
}

BitArray &BitArray::operator|=(const BitArray &b) {
    return <#initializer#>;
}

BitArray &BitArray::operator^=(const BitArray &b) {
    return <#initializer#>;
}

BitArray &BitArray::operator<<=(int n) {
    return <#initializer#>;
}

BitArray &BitArray::operator>>=(int n) {
    return <#initializer#>;
}

BitArray BitArray::operator<<(int n) const {
    return BitArray();
}

BitArray BitArray::operator>>(int n) const {
    return BitArray();
}

BitArray &BitArray::set(int n, bool val) {
    return <#initializer#>;
}

BitArray &BitArray::set() {
    return <#initializer#>;
}

BitArray &BitArray::reset(int n) {
    return <#initializer#>;
}

BitArray &BitArray::reset() {
    return <#initializer#>;
}

bool BitArray::any() const {
    return false;
}

bool BitArray::none() const {
    return false;
}

BitArray BitArray::operator~() const {
    return BitArray();
}

int BitArray::count() const {
    return 0;
}

bool BitArray::operator[](int i) const {
    return false;
}

int BitArray::size() const {
    return 0;
}

int BitArray::capacity() const {
    return 0;
}

bool BitArray::empty() const {
    return false;
}

std::string BitArray::to_string() const {
    return nullptr;
}

bool operator==(const BitArray & a, const BitArray & b){
    return false;
}

bool operator!=(const BitArray & a, const BitArray & b){
    return false;
}

BitArray operator&(const BitArray& b1, const BitArray& b2){
    return 0;
}

BitArray operator|(const BitArray& b1, const BitArray& b2){
    return 0;
}

BitArray operator^(const BitArray& b1, const BitArray& b2){
    return 0;
}
