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

    vector<pair<long long, string>> result = storageStatistic.getStatistic();

    vector<pair<long long, string>>
    correctAnswer = {{3, "aboba"}, {2, "abibeb"}, {1, "bob"}, {1, "biboba"}};

    ASSERT_EQ(result, correctAnswer);
}

TEST(StatisticStorageTests, RegisterDependencyTest) {
    vector<string> test = {"ABoBa", "aboba", "biboba", "abibeb",
                           "abibeb", "aboba", "bob"};

    StatisticStorage storageStatistic;
    storageStatistic.addToStorage(test);

    vector<pair<long long, string>> result =
            {storageStatistic.getStatistic()};

    vector<pair<long long, string>>
            correctAnswer = {{2, "aboba"}, {2, "abibeb"}, {1, "bob"}, {1, "biboba"}, {1, "ABoBa"}};

    ASSERT_EQ(result, correctAnswer);
}
