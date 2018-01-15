#include "Section.hpp"

//#define DEBUGINI

namespace IniInterpreter
{

    Section::Section() {}

    Variable& Section::operator[](std::string name)
    {
        return Variables[name];
    }

    void Section::addVariable(std::string name, std::string value)
    {
        Variables[name] = Variable(value);
    }

    bool Section::isVariable(std::string name) const
    {
        return Variables.count(name);
    }
}
