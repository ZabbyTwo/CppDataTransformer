#include <iostream>
#include <string>

#include "dataTransformer/dataTransformer.hpp"
#include "tests/unitTests.hpp"

int main()
{
    char delimiter{';'};
    std::string csvPath{"../resources/csv.csv"};

    csvFile csvFile(delimiter, csvPath);

    createXmlFromCsv(csvFile);

    runCsvFileUnitTest();

    return 0;
}
