#include "FileReader.h"
#include "Parser.h"
#include "StatisticStorage.h"
#include "CSVFileWriter.h"

int main(int argc, char** argv) {
    if (argc < 3){
        return 1;
    }
    FileReader fileReader(argv[1]);
    fileReader.open();
    StatisticStorage storageStatistic;
    while (fileReader.hasNext()) {
        Parser parser;
        string str = std::move(fileReader.next());
        parser.parse(&str);
        storageStatistic.addToStorage(parser.getParsedString());
    }
    fileReader.close();
    CSVFileWriter csvFileWriter(argv[2]);
    csvFileWriter.open();
    for (const auto& strToWrite: storageStatistic.getStatistic()){
        const vector<string> v = {strToWrite.second, std::to_string(strToWrite.first),
                                  std::to_string((double)strToWrite.first /
                                  (double)storageStatistic.getTotalAmountOfWords() * 100)};
        csvFileWriter.writeData(v, ';');
    }
    storageStatistic.clearMap();
    csvFileWriter.close();
    return 0;
}