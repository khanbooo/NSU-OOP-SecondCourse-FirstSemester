//
// Created by shark on 28.10.2023.
//

#include "CSVFileWriter.h"

CSVFileWriter::CSVFileWriter(string filename) {
    fileName = std::move(filename);
}

void CSVFileWriter::open() {
    f.open(fileName, std::ios::out);
}

void CSVFileWriter::close() {
    f.close();
}

void CSVFileWriter::writeData(const vector<string>& vec, const char delimiter) {
    for (int i = 0; i < vec.size() - 1; i++){
        f << vec[i] << delimiter;
    }
    f << vec[vec.size() - 1] << '\n';
}
