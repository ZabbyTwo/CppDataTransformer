#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include "csvFile/csvFile.hpp"

int main()
{
    char delimiter{';'};
    std::string csvPath{"/home/luis/Projects/CppDataTransformer/resources/csvTest.csv"};

    csvFile csvFile(delimiter, csvPath);

    createXML(csvFile);

    return 0;
}

