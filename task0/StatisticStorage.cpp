//
// Created by shark on 28.10.2023.
//

#include "StatisticStorage.h"

StatisticStorage::StatisticStorage() = default;

void StatisticStorage::clearMap() {
    mp.clear();
}

void StatisticStorage::sortStatistic(vector<pair<long long, string>> * vec) {
    std::sort(vec->rbegin(), vec->rend());
}

void StatisticStorage::convertMapToVector(vector<pair<long long, string>> * vec) {
    for (const auto& wordStatistic: mp){
        vec->emplace_back(wordStatistic.second, wordStatistic.first);
    }
    clearMap();
}

void StatisticStorage::addToStorage(const vector<string>& vec) {
    for (const string& s: vec){
        mp[s]++; //counting occurrences
        totalAmountOfWords++;
    }
}

vector<pair<long long, string>> StatisticStorage::getStatistic() {
    vector<pair<long long, string>> vec;
    vec.reserve(mp.size());
    convertMapToVector(&vec);
    sortStatistic(&vec);
    return vec;
}

long long StatisticStorage::getTotalAmountOfWords() const {
    return totalAmountOfWords;
}
