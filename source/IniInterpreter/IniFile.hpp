#ifndef INILOADER_H

#define INILOADER_H

#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include "Section.hpp"

namespace IniInterpreter
{

    class IniFile
    {
            enum CommandType
            {
                NEWSECTION, VARIABLE, COMMENT
            };
            std::string path;
            VariableMap globalVariables;

            static void cut(std::string string, char character, std::string& first, std::string& second);
            static std::string convertFromUTF16(std::string string);
            static CommandType getCommandType(std::string command, bool UTF16);
        public:
            static std::ostream* errorStream;
            std::vector<std::pair<std::string, Section>> sections;
            IniFile();
            IniFile(std::string inputPath, bool UTF16 = false);
            const Section* getSection(std::string name);
            VariableMap& getGlobalVariables();
            operator bool() const;
            Section& operator[](const char* name);
            Section& operator[](std::string name);
            std::vector<std::pair<std::string, Section>>::iterator begin();
            std::vector<std::pair<std::string, Section>>::iterator end();
            void setPath(std::string name);
            void debug() const;
            void debugVariable(const Variable& toDebug) const;
            void loadFromFile(bool UTF16);
            void loadFromFile(std::string name, bool UTF16);
            void saveToFile(std::string outputPath) const;
    };

}

#endif
