//
// Created by shark on 07.11.2023.
//
//
// Created by shark on 06.11.2023.
//

#include "gtest/gtest.h"
#include "../StatisticStorage.h"

TEST(StatisticStorageTests, SomeText) {
    vector<string> test = {"aboba", "aboba", "biboba", "abibeb",
                                    "abibeb", "aboba", "bob"};

    StatisticStorage storageStatistic;
    storageStatistic.addToStorage(test);

    pair<vector<pair<long long, string>>, unsigned short> result =
            {storageStatistic.getStatistic(), storageStatistic.getTotalAmountOfWords()};

    pair<vector<pair<long long, string>>, unsigned short>
    correctAnswer = {{{3, "aboba"}, {2, "abibeb"}, {1, "bob"}, {1, "biboba"}}, 7};

    ASSERT_EQ(result, correctAnswer);
}
