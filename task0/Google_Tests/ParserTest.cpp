//
// Created by shark on 06.11.2023.
//

#include "gtest/gtest.h"
#include "../Parser.h"

TEST(ParserTests, OneWord) {
    Parser parser;
    string testString = "Word";
    parser.parse(&testString);
    vector<string> correctAnswer = {"Word"};
    ASSERT_EQ(parser.getParsedString(), correctAnswer);
}

TEST(ParserTests, SomeText) {
    Parser parser;
    string testString = "askfjgho0q oii 9tidjsgoj oirga  9uqw4toiuwiogjsdlkgj asoigosdjglk  lzksg";
    parser.parse(&testString);
    vector<string> correctAnswer = {"askfjgho0q", "oii", "9tidjsgoj", "oirga",
                                    "9uqw4toiuwiogjsdlkgj", "asoigosdjglk", "lzksg"};
    ASSERT_EQ(parser.getParsedString(), correctAnswer);
}
