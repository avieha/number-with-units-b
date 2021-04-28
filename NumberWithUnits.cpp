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
#include <iterator>
#include <map>
#include "NumberWithUnits.hpp"

using namespace std;
using namespace ariel;

namespace ariel
{
    const double EPS = 0.001;
    static map<string, map<string, double>> dict;

    // constructor
    ariel::NumberWithUnits::NumberWithUnits(double number, const string &unit)
    {
        if (dict.count(unit) == 0)
        {
            throw("type isn't known");
        }
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
        if (!file)
        {
            throw "file is unreadable";
        }
        string first_unit;
        string second_unit;
        string temp;
        double d1 = 0;
        double d2 = 0;
        while (file >> d1 >> first_unit >> temp >> d2 >> second_unit)
        {
            dict[first_unit][second_unit] = d2;
            dict[second_unit][first_unit] = d1 / d2;

            /** Example: **/
            //"1 kg(first_unit) = 1000(d2) g(second_unit)"
            //"1 ton(first_unit) = 1000(d2) kg(second_unit)"

            /*** Update first_unit neighbors ***/
            for (auto &itr : dict[first_unit])
            {
                if (itr.first != second_unit && dict.at(second_unit).count(itr.first) == 0)
                {
                    double d3 = dict[first_unit][itr.first] * dict[second_unit][first_unit];
                    dict[second_unit][itr.first] = d3;
                    dict[itr.first][second_unit] = d1 / d3;
                }
            }

            /*** Update second_unit neighbors ***/
            for (auto &itr2 : dict[second_unit])
            {
                if (itr2.first != first_unit && dict.at(first_unit).count(itr2.first) == 0)
                {
                    double d3 = dict[second_unit][itr2.first] * dict[first_unit][second_unit];
                    dict[first_unit][itr2.first] = d3;
                    dict[itr2.first][first_unit] = d1 / d3;
                }
            }
        }
    };

    double NumberWithUnits::convert(const double &val, const string &s, const string &t)
    {
        if (s == t)
        {
            return val;
        }
        if (dict[t][s]==0)
        {
            throw "cant convert diff types!";
        }
        return val * dict[t][s];
    }

    void NumberWithUnits::print_dict()
    {
        map<string, map<string, double>>::iterator it;
        map<string, double>::iterator it2;
        for (it = dict.begin(); it != dict.end(); it++)
        {
            cout << it->first << ":";
            for (it2 = it->second.begin(); it2 != it->second.end(); it2++)
            {
                cout << " [" << it2->first << "]=" << it2->second;
            }
            cout << endl;
        }
        cout << endl;
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
        double sum = 0;
        sum = this->number + convert(num.number, this->unit, num.unit);
        return NumberWithUnits{sum, this->unit};
    }

    // binary addition and save
    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &num2)
    {
        this->number += convert(num2.number, this->unit, num2.unit);
        return *this;
    }

    // unary substraction
    NumberWithUnits NumberWithUnits::operator-()
    {
        NumberWithUnits res(-this->number, this->unit);
        return res;
    }

    // binary substraction
    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &num1)
    {
        double sum = 0;
        sum = this->number + convert(-num1.number, this->unit, num1.unit);
        return NumberWithUnits{sum, this->unit};
    }

    // binary substraction and save
    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &num1)
    {
        this->number -= convert(num1.number, this->unit, num1.unit);
        return *this;
    }

    /*** comparison operators ***/
    /****************************/

    // greater than operator
    bool NumberWithUnits::operator>(const NumberWithUnits &num1) const
    {
        double r = this->number - convert(num1.number, this->unit, num1.unit);
        return r >= EPS;
    }

    // greater than/equal operator
    bool NumberWithUnits::operator>=(const NumberWithUnits &num1) const
    {
        double r = this->number - convert(num1.number, this->unit, num1.unit);
        return r >= -EPS;
    }

    // smaller than operator
    bool NumberWithUnits::operator<(const NumberWithUnits &num1) const
    {
        double r = this->number - convert(num1.number, this->unit, num1.unit);
        return r <= -EPS;
    }

    // smaller than/equal operator
    bool ariel::NumberWithUnits::operator<=(const NumberWithUnits &num1) const
    {
        double r = this->number - convert(num1.number, this->unit, num1.unit);
        return r <= EPS;
    }

    // equal operator
    bool NumberWithUnits::operator==(const NumberWithUnits &num1) const
    {
        double a = this->number;
        double b = convert(num1.number, this->unit, num1.unit);
        double sum = abs(a - b);
        return sum >= 0 && sum <= EPS;
    }

    // not equal operator
    bool NumberWithUnits::operator!=(const NumberWithUnits &num1) const
    {
        double a = this->number;
        double b = convert(num1.number, this->unit, num1.unit);
        double sum = a - b;
        return sum < (-EPS) || sum > EPS;
    }

    /*** increasing and dicreasing operators ***/
    /*******************************************/

    // prefix addition
    NumberWithUnits &NumberWithUnits::operator++()
    {
        this->number++;
        return *this;
    }

    // prefix substraction
    NumberWithUnits &NumberWithUnits::operator--()
    {
        this->number--;
        return *this;
    }

    // postfix addition
    NumberWithUnits NumberWithUnits::operator++(int)
    {
        return NumberWithUnits{(this->number)++, this->unit};
    }

    // postfix substraction
    NumberWithUnits NumberWithUnits::operator--(const int n)
    {
        return NumberWithUnits{(this->number)--, this->unit};
    }

    /***  multiplication operator ***/
    /********************************/

    NumberWithUnits operator*(const NumberWithUnits &num1, const double x)
    {
        return NumberWithUnits(num1.number * x, num1.unit);
    }

    NumberWithUnits operator*(const double x, const NumberWithUnits &num2)
    {
        return NumberWithUnits(num2.number * x, num2.unit);
    }

    /*** input and output operators ***/
    /**********************************/

    // input operator
    istream &operator>>(istream &is, NumberWithUnits &num1)
    {
        double number = 0;
        string unit;
        char c = ' ';

        is >> number;
        is >> c;

        while (c != ']')
        {
            if (c != '[')
            {
                unit += c;
            }
            is >> c;
        }
        if (dict[unit].empty())
        {
            throw "the unit doesnt exist";
        }
        num1.number = number;
        num1.unit = unit;
        return is;
    }

    // output operator
    ostream &operator<<(ostream &os, const NumberWithUnits &num)
    {
        double d = num.number;
        string s = num.unit;
        os << d << "[" << s << "]";
        return os;
    }

    NumberWithUnits::~NumberWithUnits(){};
}