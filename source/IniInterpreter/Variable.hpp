#ifndef INIVAR_H
#define INIVAR_H
#include <vector>
#include <string>
#include <locale>
#include <iostream>

namespace IniInterpreter
{
    class Variable
    {
            std::string value;
            static bool stringAsBool(const std::string val);
        public:
            Variable();
            void setValue(std::string val);
            Variable(const std::string& val);
            Variable(const double& val);
            Variable(const int& val);
            Variable(const bool& val);
            operator int() const;
            operator double() const;
            operator std::string() const;
            operator bool() const;
            Variable& operator=(const std::string& val);
            Variable& operator=(const double& val);
            Variable& operator=(const int& val);
            Variable& operator=(const bool& val);
    };
}

#endif
