//
// Created by shark on 11.11.2023.
//

#include "gtest/gtest.h"
#include "../CSVFileWriter.h"
#include "../StatisticStorage.h"

TEST(CSVFileWriterTests, EmptyText) {
    vector<string> test = {};

    StatisticStorage storageStatistic;
    storageStatistic.addToStorage(test);

    CSVFileWriter csvFileWriter("output.csv");
    csvFileWriter.open();
    for (const auto& strToWrite: storageStatistic.getStatistic()){
        const vector<string> v = {strToWrite.second, std::to_string(strToWrite.first),
                                  std::to_string(storageStatistic.getTotalAmountOfWords())};
        csvFileWriter.writeData(v, ';');
    }
    csvFileWriter.close();

    std::ifstream test_file("output.csv");
    std::string line;

    std::getline(test_file, line);
    ASSERT_EQ(line, "");
}

TEST(CSVFileWriterTests, SomeText) {
    vector<string> test = {"aboba", "aboba", "biboba", "abibeb",
                           "abibeb", "aboba", "bob"};

    StatisticStorage storageStatistic;
    storageStatistic.addToStorage(test);

    CSVFileWriter csvFileWriter("output.csv");
    csvFileWriter.open();
    for (const auto& strToWrite: storageStatistic.getStatistic()){
        const vector<string> v = {strToWrite.second, std::to_string(strToWrite.first),
                                  std::to_string((double)strToWrite.first /
                                                 (double)storageStatistic.getTotalAmountOfWords() * 100)};
        csvFileWriter.writeData(v, ';');
    }
    csvFileWriter.close();

    std::ifstream test_file("output.csv");
    std::string line;

    std::getline(test_file, line);
    ASSERT_EQ(line, "aboba;3;42.857143");

    std::getline(test_file, line);
    ASSERT_EQ(line, "abibeb;2;28.571429");

    std::getline(test_file, line);
    ASSERT_EQ(line, "bob;1;14.285714");

    std::getline(test_file, line);
    ASSERT_EQ(line, "biboba;1;14.285714");
}
