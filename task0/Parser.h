//
// Created by shark on 28.10.2023.
//

#ifndef TASK0_PARSER_H
#define TASK0_PARSER_H


#include "string"
#include "vector"

using std::string;
using std::vector;
// Парсинг строки на лексемы
class Parser {
private:
    vector<string> parsedString;
public:
    explicit Parser();

    // функция парсинга
    void parse(const string *s);

    // получить распарcенную строку
    vector<string> getParsedString();
};

#endif //TASK0_PARSER_H
