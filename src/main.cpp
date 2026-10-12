#include <iostream>
#include <string>

#include "csvFile/csvFile.hpp"
#include "tests/unitTests.hpp"

int main()
{
    char delimiter{';'};
    std::string csvPath{"/home/luis/Projects/CppDataTransformer/resources/csv.csv"};

    csvFile csvFile(delimiter, csvPath);

    createXmlFromCsv(csvFile);

    runCsvFileUnitTest();

    return 0;
}
