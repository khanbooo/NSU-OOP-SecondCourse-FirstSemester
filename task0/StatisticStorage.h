//
// Created by shark on 28.10.2023.
//

#ifndef TASK0_STATISTICSTORAGE_H
#define TASK0_STATISTICSTORAGE_H


#include "unordered_map"
#include "vector"
#include "string"
#include "algorithm"

using std::unordered_map;
using std::vector;
using std::string;
using std::pair;
//Хранилище данных
class StatisticStorage {
private:
    unordered_map <string, long long> mp;
    long long totalAmountOfWords = 0;

    // перевести мапу в вектор
    void convertMapToVector(vector<pair<long long, string>> * vec) const;

    // отспортировать данные
    static void sortStatistic(vector<pair<long long, string>> * vec);
public:
    explicit StatisticStorage();

    // добавить данные в хранилище
    void addToStorage(const vector<string>& vec);

    // получить данные из хранилища
    vector<pair<long long, string>> getStatistic() const;

    // получить общее количество слов
    long long getTotalAmountOfWords() const;

    // очистить мапу
    void clearMap();

};


#endif //TASK0_STATISTICSTORAGE_H
