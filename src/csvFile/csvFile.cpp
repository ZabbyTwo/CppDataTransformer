#include "csvFile.hpp"

void createXML(const csvFile &csvData)
{
    // XML filename
    std::string xmlFilename{"./resources/xmltest.xml"};
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