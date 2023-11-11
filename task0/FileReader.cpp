//
// Created by shark on 28.10.2023.
//

#include "FileReader.h"

FileReader::FileReader(string filename) {
    fileName = std::move(filename);
}

void FileReader::open() {
    f.open(fileName, std::ios::in);
}

string FileReader::next() {
    std::string str;
    std::getline(f, str);
    return str;
}

bool FileReader::hasNext() {
    return f.peek() != EOF;
}

void FileReader::close() {
    f.close();
}
