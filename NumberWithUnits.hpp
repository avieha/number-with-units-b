#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

namespace ariel
{
    class NumberWithUnits
    {

    private:
    double number;
    string unit;

    public:
        // constructor and distructor
        NumberWithUnits(double number, const string& unit);
        ~NumberWithUnits();

        // placement operator
        NumberWithUnits& operator=(const NumberWithUnits &num);

        // function for reading the units from a given file
        static void read_units(ifstream &file);

        /*** arithmetic operators ***/
        /****************************/

        // unary addition
        ariel::NumberWithUnits operator+();

        // binary addition
        NumberWithUnits operator+(const NumberWithUnits &num1);

        // binary addition and save
        NumberWithUnits& operator+=(ariel::NumberWithUnits& num2);

        // unary substraction
        NumberWithUnits operator-();

        // binary substraction
        const NumberWithUnits operator-(const NumberWithUnits &num1) const;

        // binary substraction and save
        const NumberWithUnits& operator-=(const NumberWithUnits &num1);

        /*** comparison operators ***/
        /****************************/

        // greater than operator
        const bool operator>(const NumberWithUnits &num1) const;
        
        // greater than/equal operator
        bool operator>=(const NumberWithUnits &num1) const;
        
        // smaller than operator
        bool operator<(const NumberWithUnits &num1) const;
        
        // smaller than/equal operator
        bool operator<=(const NumberWithUnits &num1) const;
        
        // equal operator
        bool operator==(const NumberWithUnits &num1) const;
        
        // not equal operator
        bool operator!=(const NumberWithUnits &num1) const;
        

        /*** increasing and dicreasing operators ***/
        /*******************************************/

        // prefix addition
        NumberWithUnits& operator++();
        
        // prefix substraction
        NumberWithUnits& operator--();
        
        // postfix addition
        const NumberWithUnits& operator++(int);

        // postfix substraction
        const NumberWithUnits& operator--(const int n);

        /***  multiplication operator ***/
        /********************************/

        friend NumberWithUnits operator*(const NumberWithUnits& num,const double &x);
        friend NumberWithUnits operator*(const double &x, const NumberWithUnits& num);

        /*** input and output operators ***/
        /**********************************/

        // input operator
        friend istream &operator>>(istream& is,NumberWithUnits &num);

        // output operator
        friend ostream &operator<<(ostream& os, const NumberWithUnits &num);
    };

}