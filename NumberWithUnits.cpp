/**
 * Demo file for the exercise on numbers with units
 *
 * @author Aviem Hadar
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <ctype.h>
#include "NumberWithUnits.hpp"

using namespace std;
using namespace ariel;

namespace ariel
{
    static map<string, map<string, double>> dict;

    // constructor
    ariel::NumberWithUnits::NumberWithUnits(double number, const string &unit)
    {
        this->number = number;
        this->unit = unit;
    }

    // placement operator
    NumberWithUnits &NumberWithUnits::operator=(const NumberWithUnits &num)
    {
        this->number = num.number;
        this->unit = num.unit;
        return *this;
    }

    // function for reading units from a file
    void NumberWithUnits::read_units(ifstream &file)
    {
        string line;
        while (file)
        {
            getline(file, line);
            string first_unit;
            string second_unit;
            string third_unit;
            for (size_t i = 0; i < line.length(); i++)
            {
                bool flag;
                if (line.at(i) == ' ')
                {
                    continue;
                }
                if (isalpha(line.at(i)))
                {
                    if (!flag)
                    {
                        first_unit += line.at(i);
                    }
                    else
                    {
                        third_unit += line.at(i);
                    }
                }
                if (isdigit(line.at(i)) && i != 0)
                {
                    flag = true;
                    second_unit += line.at(i);
                }
            }
            dict[first_unit][third_unit] = stod(second_unit);
            dict[third_unit][first_unit] = 1 / (stod(second_unit));
        }
    };

    bool check(const string &s, const string &t)
    {
        if (dict[s][t] != NULL)
            return true;
        throw "unconvertable addition";
        return false;
    }

    double convert(const double first, const double second, const string s,const string t){
        if (dict[s][t])
        {
            double sum;
            sum = first + dict[s][t] * second;
            return sum;
        }
        return 0;
    }

    /*** arithmetic operators ***/
    /****************************/

    // unary addition
    NumberWithUnits NumberWithUnits::operator+()
    {
        return *this;
    }

    // binary addition
    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &num)
    {
        double sum;
        if (check(this->unit, num.unit))
        {
            sum = convert(this->number,num.number,this->unit, num.unit);
        }
        return NumberWithUnits{sum,this->unit};
    }

    // binary addition and save
    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &num2)
    {
        if (check(this->unit, num2.unit))
        {
            this->number = convert(this->number,num2.number,this->unit,num2.unit);
        }
        return *this;
    }

    // unary substraction
    NumberWithUnits NumberWithUnits::operator-() { 
        this->number = (-1)*this->number;
        return *this;
    }

    // binary substraction
    const NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &num1) const { return NumberWithUnits(0, "km"); }

    // binary substraction and save
    const NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &num1)
    {
        return num1;
    }

    /*** comparison operators ***/
    /****************************/

    // greater than operator
    const bool NumberWithUnits::operator>(const NumberWithUnits &num1) const
    {
        return true;
    }

    // greater than/equal operator
    bool NumberWithUnits::operator>=(const NumberWithUnits &num1) const
    {
        return true;
    }

    // smaller than operator
    bool NumberWithUnits::operator<(const NumberWithUnits &num1) const
    {
        return true;
    }

    // smaller than/equal operator
    bool ariel::NumberWithUnits::operator<=(const NumberWithUnits &num1) const
    {
        return true;
    }

    // equal operator
    bool ariel::NumberWithUnits::operator==(const NumberWithUnits &num1) const
    {
        return true;
    }

    // not equal operator
    bool NumberWithUnits::operator!=(const NumberWithUnits &num1) const
    {
        return true;
    }

    /*** increasing and dicreasing operators ***/
    /*******************************************/

    // prefix addition
    NumberWithUnits &NumberWithUnits::operator++()
    {
        return *this;
    }

    // prefix substraction
    NumberWithUnits &NumberWithUnits::operator--()
    {
        return *this;
    }

    // postfix addition
    const NumberWithUnits &NumberWithUnits::operator++(int)
    {
        return *this;
    }

    // postfix substraction
    const NumberWithUnits &NumberWithUnits::operator--(const int n)
    {
        return *this;
    }

    /***  multiplication operator ***/
    /********************************/

    NumberWithUnits operator*(const NumberWithUnits &num, const double &x)
    {
        return num;
    }

    NumberWithUnits operator*(const double &x, const NumberWithUnits &num)
    {
        return num;
    }

    /*** input and output operators ***/
    /**********************************/

    // input operator
    istream &operator>>(istream &is, NumberWithUnits &num)
    {
        string s = "right";
        is >> s;
        return is;
    }

    // output operator
    ostream &operator<<(ostream &os, const NumberWithUnits &num)
    {
        double s = num.number;
        os << s;
        return os;
    }

    NumberWithUnits::~NumberWithUnits(){};

}