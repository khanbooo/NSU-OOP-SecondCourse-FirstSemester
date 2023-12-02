//
// Created by shark on 28.10.2023.
//

#include "Parser.h"

Parser::Parser()= default;

void Parser::parse(const string *s) {
    string currentWord;
    for (const char ch: *s){
        if (isalnum(ch)) {
            currentWord += ch;
        }
        else{
            if (!currentWord.empty()){
                parsedString.emplace_back(currentWord);
                currentWord.clear();
            }
        }
    }
    if (!currentWord.empty()) {
        parsedString.emplace_back(currentWord);
        currentWord.clear();
    }
}

vector<string> Parser::getParsedString() {
    return parsedString;
}
