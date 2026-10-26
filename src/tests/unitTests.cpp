#include <iostream>
#include <string>
#include <fstream>
#include <cassert>

#include "unitTests.hpp"
#include "../dataTransformer/dataTransformer.hpp"

bool runCsvFileUnitTest()
{
    std::string testPath{"test_data.csv"};
    std::ofstream testFile(testPath);
    testFile << "Name;Age;City\n";
    testFile << "Luis;21;Vienna\n";
    testFile << "Emma;20;Berlin\n";
    testFile.close();

    char delimiter{';'};
    csvFile csv(delimiter, testPath);

    auto headers = csv.getHeaders();
    assert(headers.size() == 3 && "Header count should be 3");
    assert(headers[0] == "Name" && "First header should be Name");
    assert(csv.getSpecificHeaderByPos(1) == "Age" && "Second header should be Age");
    assert(csv.doesHeaderExists("City") == true && "Should find City header");

    auto values = csv.getValues();
    assert(values.size() == 2 && "Should have 2 rows of data");
    assert(values[0].size() == 3 && "First row should have 3 columns");
    assert(values[0][0] == "Luis" && "First value should be Luis");
    assert(values[1][2] == "Berlin" && "Last value should be Berlin");
    assert(values[0][1] == "21" && "Luis age should be 21");
    // std::stoi to check int value
    assert(std::stoi(values[0][1]) == 21 && "Luis age should be 21");
    assert(csv.doesValueExists("Emma") == true && "Should find Emma in values");

    std::remove(testPath.c_str());

    std::cout << "All csvFile tests passed!\n";
    return true;
}