#include "dataTransformer.hpp"

void createXmlFromCsv(const csvFile &csvData)
{
    // XML filename
    std::string xmlFilename{"../resources/xml.xml"};
    // Top level Root Name
    std::string topLevelName{"root"};
    // Each Record XML Name
    std::string recordXmlName{"row"};

    std::ofstream xmlFile{xmlFilename};

    if (xmlFile.is_open())
    {
        xmlFile << "<?xml version='1.0' encoding='UTF-8'?>";
        xmlFile << "<" << topLevelName << ">";
        for (const auto &um : csvData.getValues())
        {
            xmlFile << "<" << recordXmlName << ">";

            for (int i{0}; i < csvData.getHeaders().size(); i++)
            {
                xmlFile << "<" << csvData.getHeaders().at(i) << ">" << um.at(i) << "</" << csvData.getHeaders().at(i) << ">";
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