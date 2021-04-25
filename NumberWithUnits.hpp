#include <stddef.h>
#include <iostream>
#include <map>
using namespace std;

namespace ariel {
    class NumberWithUnits{
        double number;
        string unit;

        public: 
        friend ostream& operator<<(ostream& os, const NumberWithUnits &nwu); 
        friend istream& operator>>(istream& input, NumberWithUnits& nwu);

        friend NumberWithUnits operator+(const NumberWithUnits& nwu_a,const NumberWithUnits& nwu_b);
        friend NumberWithUnits operator-(const NumberWithUnits& nwu_a,const NumberWithUnits& nwu_b);
        
        friend bool operator!=(const NumberWithUnits& nwu_a,const NumberWithUnits& nwu_b);
        
        friend bool operator==(const NumberWithUnits& nwu_a,const NumberWithUnits& nwu_b);
        friend bool operator==(NumberWithUnits& nwu_a,NumberWithUnits& nwu_b);
        
        friend bool operator<(const NumberWithUnits& nwu_a,const NumberWithUnits& nwu_b);
        friend bool operator>(const NumberWithUnits& nwu_a,const NumberWithUnits& nwu_b);
        friend bool  operator>=(const NumberWithUnits& nwu_a,const NumberWithUnits& nwu_b);
        friend bool  operator<=(const NumberWithUnits& nwu_a,const NumberWithUnits& nwu_b);
        

        
        
        friend NumberWithUnits operator-(const NumberWithUnits& nwu);
        friend NumberWithUnits operator+(const NumberWithUnits& nwu);
        
        friend NumberWithUnits operator++(NumberWithUnits& nwu, int dummy_flag);
        friend NumberWithUnits& operator++(NumberWithUnits& nwu);
        
        friend NumberWithUnits operator--(NumberWithUnits& nwu, int dummy_flag);
        friend NumberWithUnits& operator--(NumberWithUnits& nwu);
        
        friend NumberWithUnits operator*(const double multiply_by,const NumberWithUnits& nwu);
        friend NumberWithUnits operator*(const NumberWithUnits& nwu, const double multiply_by);
        
        
        friend NumberWithUnits& operator+=(NumberWithUnits& nwu_a, const NumberWithUnits& nwu_b);
        friend NumberWithUnits& operator-=(NumberWithUnits& nwu_a, const NumberWithUnits& nwu_b);
        
        friend NumberWithUnits operator+=(const NumberWithUnits& nwu_a, const NumberWithUnits& nwu_b);
        friend NumberWithUnits operator-=(const NumberWithUnits& nwu_a, const NumberWithUnits& nwu_b);
        
        NumberWithUnits(double number,string unit);
        
        static void read_units(ifstream& units_file);
        
    };
}