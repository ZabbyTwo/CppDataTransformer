#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

class csvFile
{
private:
    std::vector<std::string> m_headers;
    std::vector<std::vector<std::string>> m_values;

    static inline auto lambdaCout = [](auto n)
    {
        std::cout << n << " ";
    };

public:
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
                        m_headers.push_back(currentValue);
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
                    m_values.push_back(valuesTemp);
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
        std::for_each(m_headers.begin(), m_headers.end(), lambdaCout);
        std::cout << "\n";
        std::cout << "Values: " << "\n";
        for (auto v1 : m_values)
        {
            std::for_each(v1.begin(), v1.end(), lambdaCout);
            std::cout << "\n";
        }
    }

    std::string getSpecificHeaderByPos(const int& pos) const
    {
        return m_headers.at(pos);
    }

    bool doesHeaderExists(const std::string& name) const
    {
        for (auto header : m_headers)
        {
            if (header == name)
            {
                return true;
            }
        }
        std::cerr << "NO HEADER FOUND";
        return false;
    }

    bool doesValueExists(const std::string& value) const
    {
        for (auto row : m_values)
        {
            for (auto value_for : row)
            {
                if (value_for == value)
                {
                    return true;
                }
            }
        }
        std::cerr << "NO VALUE FOUND";
        return false;
    }

    const std::vector<std::string> &getHeaders() const
    {
        return m_headers;
    }

    const std::vector<std::vector<std::string>> &getValues() const
    {
        return m_values;
    }
};

void createXmlFromCsv(const csvFile &csvData);