#pragma once

#ifndef INISECTION_H
#define INISECTION_H
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include "Variable.hpp"
namespace IniInterpreter
{

    typedef std::map<std::string, Variable> VariableMap;
    class Section
    {

        public:
            VariableMap Variables;
            Section();
            void addVariable(std::string name, std::string value);
            bool isVariable(std::string name) const;

            Variable& operator[](std::string name);
            template<typename T> T getVariable(std::string name)
            {
                if(Variables.count(name) == 0) return T();

                return (T)Variables[name];
            }

    };

}

#endif
