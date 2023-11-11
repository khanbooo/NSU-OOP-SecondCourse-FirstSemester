//
// Created by shark on 29.10.2023.
//

#include "gtest/gtest.h"
#include "../FileReader.h"

TEST(FileReaderTests, EmptyTest) {
    FileReader fileReader("input.txt");
    fileReader.open();
    ASSERT_FALSE(fileReader.hasNext());
}
