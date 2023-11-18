//
// Created by shark on 28.10.2023.
//

#ifndef TASK0_CSVFILEWRITER_H
#define TASK0_CSVFILEWRITER_H


#include "string"
#include "vector"
#include "fstream"

using std::string;
using std::vector;
using std::ofstream;
using std::pair;
// Запись данных
class CSVFileWriter {
private:
    string fileName;
    ofstream f;
public:
    explicit CSVFileWriter(string filename);

    // открыть файл
    void open();

    // закрыть файл
    void close();

    // записать данные в файл
    void writeData(const vector<string>& vec, char delimiter);
};


#endif //TASK0_CSVFILEWRITER_H
