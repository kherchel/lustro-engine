#include "IniFile.hpp"

namespace IniInterpreter
{

    std::ostream* IniFile::errorStream = &std::cerr;

    void IniFile::cut(std::string string, char character, std::string& first, std::string& second)
    {
        std::size_t pos = string.find(character);
        first = string.substr(0, pos);
        second = string.substr(pos+1);
    }

    std::string IniFile::convertFromUTF16(std::string string)
    {
        std::string ret = "";

        for(size_t a = 0; a != string.length()/2; a++)
        {
            ret += string[2*a+1];
        }

        return ret;
    }

    IniFile::CommandType IniFile::getCommandType(std::string command, bool UTF16)
    {
        if(UTF16)command = IniFile::convertFromUTF16(command);

        if(command[0] == '[')
            return NEWSECTION;

        if(command[0] == ';')
            return COMMENT;

        if(command.find('=') != std::string::npos)
            return VARIABLE;

        return COMMENT;
    }

    IniFile::IniFile() : path("")
    {

    }

    IniFile::IniFile(std::string inputPath, bool UTF16) : IniFile::IniFile()
    {
        loadFromFile(inputPath, UTF16);
    }

    const Section* IniFile::getSection(std::string name)
    {
    	for(auto& i : sections) 
    		if(i.first == name)
        		return &i.second;
     	return nullptr;
    }

    IniFile::operator bool() const
    {
        return sections.size();
    }

    Section& IniFile::operator[](const char* name)
    {
    	for(auto& i : sections) 
    		if(i.first == name)
        		return i.second;
       	sections.push_back(std::pair<std::string, Section>(name, Section()));
       	return sections[sections.size()-1].second;
    }

    Section& IniFile::operator[](std::string name)
    {
    	for(auto& i : sections) 
    		if(i.first == name)
        		return i.second;
        sections.push_back(std::pair<std::string, Section>(name, Section()));
       	return sections[sections.size()-1].second;
    }

    std::vector<std::pair<std::string, Section>>::iterator IniFile::begin()
    {
        return sections.begin();
    }

    std::vector<std::pair<std::string, Section>>::iterator IniFile::end()
    {
        return sections.end();
    }

    void IniFile::setPath(std::string name)
    {
        path = name;
    }

    VariableMap& IniFile::getGlobalVariables()
    {
        return globalVariables;
    }

    void IniFile::debugVariable(const Variable& toDebug) const
    {
        if(errorStream == nullptr) return;

        *errorStream << "[IniInterpreter] Value - " << (std::string)toDebug << '\n';
    }

    void IniFile::debug() const
    {
        if(errorStream == nullptr) return;

        *errorStream << "[IniInterpreter] Variables in " << path << ":\n[IniInterpreter] Global:\n";

        for(auto iter = globalVariables.begin(); iter != globalVariables.end(); iter++)
        {
            *errorStream << iter->first << " - ";
            debugVariable(iter->second);
        }

        for(auto iter = sections.begin(); iter != sections.end(); iter++)
        {
            *errorStream << "[IniInterpreter] Section " << iter->first << "\n";

            for(auto iter_sec = iter->second.Variables.begin(); iter_sec != iter->second.Variables.end(); iter_sec++)
            {
                *errorStream << "[IniInterpreter] " << iter_sec->first << " - ";
                debugVariable(iter_sec->second);
            }
        }

        *errorStream << "[IniInterpreter] End" << std::endl;
    }


    void IniFile::saveToFile(std::string outputPath) const
    {
        std::ofstream file(outputPath);

        for(auto iter = globalVariables.begin(); iter != globalVariables.end(); iter++)
            file << iter->first + "=" + (std::string)iter->second + "\n";

        if(globalVariables.size() != 0)file << "\n";

        for(auto iter = sections.begin(); iter != sections.end(); iter++)
        {
            file << "[" + iter->first + "]\n";

            for(auto iter_sec = iter->second.Variables.begin(); iter_sec != iter->second.Variables.end(); iter_sec++)
                file << iter_sec->first + "=" + (std::string)iter_sec->second + "\n";

            file << "\n";
        }

        file.close();
    }


    void IniFile::loadFromFile(bool UTF16)
    {
        sections.clear();

        std::ifstream file(path.c_str());

        if(!file)return;

        VariableMap* writeMap = &globalVariables;
        bool firstIteration = true;

        do
        {
            std::string command;
            getline(file, command);

            if(UTF16 && firstIteration) //Weird cutting down one letter, that's weird
                command = " " + command;

            std::string name = "", value = "";
            CommandType commandType = IniFile::getCommandType(command, UTF16);

            switch(commandType)
            {
                case NEWSECTION:
                    if(UTF16)command = IniFile::convertFromUTF16(command);

                    for(unsigned int a = 1; a < command.length(); a++)
                    {
                        if(command[a] == ']')break;

                        name += command[a];
                    }

                    sections.push_back(std::pair<std::string, Section>(name, Section()));
                    writeMap = &(sections[sections.size()-1].second.Variables);
                    break;

                case COMMENT:
                case VARIABLE:
                    break;
            }

            if(commandType != NEWSECTION && commandType != COMMENT)
            {
                cut(command, '=', name, value);

                if(UTF16)
                {
                    name = IniFile::convertFromUTF16(name);
                    value.erase(value.begin());
                    value.insert(value.end(), '\0');
                }

                (*writeMap)[name] = Variable(value);
            }

            firstIteration = false;

        } while(!file.eof());
    }


    void IniFile::loadFromFile(std::string name, bool UTF16)
    {
        path = name;
        loadFromFile(UTF16);
    }

}
