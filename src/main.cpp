#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_map>

auto lambdaCout = [](auto n)
{
    std::cout << n << " ";
};

struct csvData
{
    std::vector<std::string> headers;
    std::vector<std::vector<std::string>> values;

    void print()
    {
        std::cout << "Headers: " << "\n";
        std::for_each(headers.begin(), headers.end(), lambdaCout);
        std::cout << "\n";
        std::cout << "Values: " << "\n";
        for (auto v1 : values)
        {
            std::for_each(v1.begin(), v1.end(), lambdaCout);
            std::cout << "\n";
        }
    }
};

csvData getCsvData(char delimiter, const std::string &csvPath);
void createXML(const csvData &csvData);

int main()
{
    char delimiter{';'};
    std::string csvPath{"/home/luis/Projects/CppDataTransformer/resources/csvTest.csv"};
    csvData csvFile = getCsvData(delimiter, csvPath);

    csvFile.print();

    createXML(csvFile);

    return 0;
}

csvData getCsvData(char delimiter, const std::string &csvPath)
{
    csvData csvResult;
    std::string currentLine;
    std::string currentValue;
    std::ifstream csvFile{csvPath};

    bool isFirstLine = true;

    if (csvFile.is_open())
    {
        while (std::getline(csvFile, currentLine))
        {
            std::stringstream ss(currentLine);

            if (isFirstLine)
            {
                // header
                while (std::getline(ss, currentValue, delimiter))
                {
                    csvResult.headers.push_back(currentValue);
                }
                isFirstLine = false;
            }
            else
            {
                // values
                std::vector<std::string> valuesTemp;

                while (std::getline(ss, currentValue, delimiter))
                {
                    valuesTemp.push_back(currentValue);
                }

                // Das push_back passiert NUR, wenn wir im Daten-Block sind
                csvResult.values.push_back(valuesTemp);
            }
        }
        csvFile.close();
    }
    else
    {
        std::cerr << "Failed to open '" << csvPath << "'" << "\n";
    }

    return csvResult;
}

void createXML(const csvData &csvData)
{
    // XML filename
    std::string xmlFilename{"../resources/xmltest.xml"};
    // Top level Root Name
    std::string topLevelName{"root"};
    // Each Record XML Name
    std::string recordXmlName{"row"};

    std::ofstream xmlFile{xmlFilename};

    if (xmlFile.is_open())
    {
        xmlFile << "<?xml version='1.0' encoding='UTF-8'?>";
        xmlFile << "<" << topLevelName << ">";
        for (const auto &um : csvData.values)
        {
            xmlFile << "<" << recordXmlName << ">";

            for (int i{0}; i < csvData.headers.size(); i++)
            {
                xmlFile << "<" << csvData.headers.at(i) << ">" << um.at(i) << "</" << csvData.headers.at(i) << ">";
            }
            xmlFile << "</" << recordXmlName << ">";
        }
        xmlFile << "</" << topLevelName << ">";
        xmlFile.close();
        std::cout << xmlFilename << " got created!" << "\n";
    }
    else
    {
        std::cerr << "Failed to open '" << xmlFilename << "'" << "\n";
    }
}