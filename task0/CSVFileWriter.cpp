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

void CSVFileWriter::writeData(const vector<pair<long long int, string>>& vec,
                              long long totalAmountOfWords) {
    for (const auto& data: vec){
        f << data.second << ';' << data.first << ';' <<
          ((double)data.first) / (double)totalAmountOfWords * 100 << '\n';
    }
}
