//
// Created by shark on 28.10.2023.
//

#ifndef TASK0_FILEREADER_H
#define TASK0_FILEREADER_H


#include "string"
#include "fstream"

using std::string;
using std::ifstream;
// Чтение файла построчно
class FileReader {
private:
    string fileName;
    ifstream f;
public:
    explicit FileReader(string filename);

    // открыть файл
    void open();

    // дай след. строчку
    string next();

    // есть ли еще данные для считывания
    bool hasNext();

    // закрыть файл
    void close();
};


#endif //TASK0_FILEREADER_H
