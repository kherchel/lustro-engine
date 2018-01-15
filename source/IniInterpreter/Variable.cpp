#include "Variable.hpp"

namespace IniInterpreter
{
    bool Variable::stringAsBool(const std::string value)
    {
        if(value == "")return false;

        if(value == "true" || value == "TRUE") return true;

        if(value[0] == '0' || value == "false" || value == "FALSE") return false;

        return true;
    }

    Variable::Variable() {}

    Variable::Variable(const std::string& val) : value(val) {}

    Variable::Variable(const double& val) : value(std::to_string(val)) {}

    Variable::Variable(const int& val) : value(std::to_string(val)) {}

    Variable::Variable(const bool& val)
    {
        if(val) value = "true";
        else value = "false";
    }

    void Variable::setValue(std::string val)
    {
        value = val;
    }

    Variable::operator int() const
    {
        int ret = 0;

        try
        {
            ret = std::stoi(value);
        }
        catch(const std::invalid_argument& ia) {}

        return ret;
    }

    Variable::operator double() const
    {
        double ret = 0;
        std::locale l("");
		std::setlocale(LC_ALL, "C");
        try
        {
            ret = stod(value);
        }
        catch(const std::invalid_argument& ia) {}
		std::setlocale(LC_ALL, l.name().c_str());
        return ret;
    }

    Variable::operator std::string() const
    {
        return value;
    }

    Variable::operator bool() const
    {
        return stringAsBool(value);
    }

    Variable& Variable::operator=(const std::string& val)
    {
        value = val;
        return *this;
    }

    Variable& Variable::operator=(const double& val)
    {
        value = std::to_string(val);
        return *this;
    }

    Variable& Variable::operator=(const int& val)
    {
        value = std::to_string(val);
        return *this;
    }

    Variable& Variable::operator=(const bool& val)
    {
        if(val) value = "true";
        else value = "false";

        return *this;
    }


}
