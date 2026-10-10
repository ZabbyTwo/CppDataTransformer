#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

struct csvFile
{
    std::vector<std::string> headers;
    std::vector<std::vector<std::string>> values;

    static inline auto lambdaCout = [](auto n)
    {
        std::cout << n << " ";
    };

    csvFile(char delimiter, const std::string &csvPath)
    {
        std::string currentLine;
        std::string currentValue;
        std::ifstream file{csvPath};

        bool isFirstLine = true;

        if (file.is_open())
        {
            while (std::getline(file, currentLine))
            {
                std::stringstream ss(currentLine);

                if (isFirstLine)
                {
                    // header
                    while (std::getline(ss, currentValue, delimiter))
                    {
                        headers.push_back(currentValue);
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
                    values.push_back(valuesTemp);
                }
            }
            file.close();
        }
        else
        {
            std::cerr << "Failed to open '" << csvPath << "'" << "\n";
        }
    }

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

    std::vector<std::string> getHeaders()
    {
        return headers;
    }

    std::string getSpecificHeaderByPos(const int pos) const
    {
        return headers.at(pos);
    }

    std::string getSpecificHeaderByName(const std::string name) const
    {
        for (auto header : headers)
        {
            if (header == name)
            {
                return header;
            }
        }
    }
};

void createXML(const csvFile &csvData);