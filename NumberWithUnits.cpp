#include <iostream>
#include <fstream>
#include <exception>
#include <vector>
#include <map>
#include <math.h>
#include <algorithm>
using namespace std;


#include "NumberWithUnits.hpp"

using namespace ariel;
static const double EPSILON = 0.001;

static map< string, map<string, double>> conversion_map;


namespace ariel{
NumberWithUnits::NumberWithUnits(double number, string unit){
  if(conversion_map.count(unit) != 0)
    {this->number=number;
    this->unit=unit;}
  else
    {throw std::invalid_argument{unit + " doesn't exist in the units file"};}
 
        
} 
ostream& operator<<(ostream& os, const NumberWithUnits &nwu){
    return (os << nwu.number << "[" << nwu.unit << "]");
 }



 static istream& getAndCheckNextCharIs(istream& input, char expectedChar) {
        char actualChar=0;
        input >> actualChar;
        if (!input) {return input;}
        if (actualChar!=expectedChar){ 
            input.setstate(ios::failbit);
        }
        return input;
 } 


istream& operator>> (istream& input, NumberWithUnits& n) {

        double new_sum=0;
        string new_type;
        ios::pos_type startPosition = input.tellg();
        if ( (!(input >> new_sum)) || (!getAndCheckNextCharIs(input,'[')) || 
            (!(input >> new_type))) {
                auto errorState = input.rdstate(); 
                input.clear(); 
                input.seekg(startPosition); 
                input.clear(errorState); 
            } else {
                unsigned long index=new_type.length()-1;
                if (new_type.at(index)!=']'){
                    string xx;
                    input >> xx;
                    new_type+=xx;
                }
                index=new_type.length()-1;
                new_type=new_type.substr(0,index);   
                n=NumberWithUnits(new_sum,new_type);
            }
        return input;
    }



void NumberWithUnits::read_units(ifstream& units_file){
string unit_a;
string unit_b; 
string ignore;

double number_a = NAN;
double number_b = NAN;

while( units_file >> number_a >> unit_a >> ignore >> number_b >> unit_b ){  
   
    conversion_map[unit_a][unit_b] = pow(1+((number_a - number_b)/number_b),-1);
    conversion_map[unit_b][unit_a] = 1+((number_a - number_b)/number_b);
}

}


double convertion_coefficient(vector<string>& already_checked, double acc,bool& flag,const string& from,const string& to){
 
    map<string, double> &internal_map = conversion_map[from];
    for (map<string, double>::iterator it2 = internal_map.begin(); it2 != internal_map.end(); ++it2){ 
          if (!(find(already_checked.begin(), already_checked.end(),it2->first)!=already_checked.end()))
          {already_checked.push_back(it2->first);
          acc = (it2->second)*convertion_coefficient(already_checked, acc, flag, it2->first, to);
          }
          if (it2->first == to){
          flag = true;
         return it2->second;
          }
}
return acc;
}


double convert_unit(double number,const string& from_unit,const string& to_unit){
  double conversion_coefficient =1;
    if (from_unit != to_unit)
    {vector<string> already_checked;
      bool flag = false;
      conversion_coefficient = convertion_coefficient(already_checked,1,flag,from_unit,to_unit);
      
      if (from_unit == "mg" && to_unit == "ton")
        {conversion_coefficient = conversion_coefficient/conversion_map["g"]["mg"];}
      else if (from_unit == "hour" && to_unit == "sec")
          {conversion_coefficient = conversion_map["hour"]["min"]*conversion_map["min"]["sec"];} 
      else if (from_unit == "sec" && to_unit == "day")
          {conversion_coefficient = conversion_map["sec"]["min"]*conversion_map["min"]["hour"]*conversion_map["hour"]["day"];} 
       
       if (!flag)
        {throw logic_error{"Units do not match - [" + from_unit + "] " + "cannot be converted to"  + " [" + to_unit + "]"};}
    }
    else {
      return number;
    }
  
  return number*conversion_coefficient;
}

 NumberWithUnits operator-(const NumberWithUnits& nwu){
    return {-nwu.number,nwu.unit};
 }

 NumberWithUnits operator+(const NumberWithUnits& nwu){
    return {nwu.number,nwu.unit};
 }

 NumberWithUnits& operator++(NumberWithUnits& nwu){
    nwu.number++;
    return nwu;
 }

 NumberWithUnits operator++(NumberWithUnits& nwu, int dummy_flag){
    NumberWithUnits copy{nwu.number,nwu.unit};
    nwu.number++;
    return copy;
 }
 
 NumberWithUnits& operator--(NumberWithUnits& nwu){
    nwu.number--;
    return nwu;
 }

 NumberWithUnits operator--(NumberWithUnits& nwu, int dummy_flag){
    NumberWithUnits copy{nwu.number,nwu.unit};
    nwu.number--;
    return copy;
 }
 
 NumberWithUnits operator*(const double multiply_by,const NumberWithUnits& nwu){
   return {multiply_by*nwu.number,nwu.unit};
 }

 NumberWithUnits operator*(const NumberWithUnits& nwu, const double multiply_by){
   return {nwu.number*multiply_by,nwu.unit};
 }

 NumberWithUnits operator+(const NumberWithUnits& nwu_a,const NumberWithUnits& nwu_b){

  return {nwu_a.number + convert_unit(nwu_b.number,nwu_b.unit,nwu_a.unit), nwu_a.unit};
 }

 NumberWithUnits operator-(const NumberWithUnits& nwu_a,const NumberWithUnits& nwu_b){
   
  return NumberWithUnits(nwu_a.number - convert_unit(nwu_b.number,nwu_b.unit,nwu_a.unit), nwu_a.unit);
 }

 bool operator==(const NumberWithUnits& nwu_a,const NumberWithUnits& nwu_b){
   bool answer = false;
   if (abs(nwu_a.number - convert_unit(nwu_b.number,nwu_b.unit,nwu_a.unit ))< EPSILON)
    {answer = true;}
   return answer;
 }

  bool operator==(NumberWithUnits& nwu_a,NumberWithUnits& nwu_b){
   bool answer = false;
   if (abs(nwu_a.number - convert_unit(nwu_b.number,nwu_b.unit,nwu_a.unit))< EPSILON)
    {answer = true;}
   return answer;
 }

 bool operator!=(const NumberWithUnits& nwu_a,const NumberWithUnits& nwu_b){
 return (!(nwu_a==nwu_b));
 }

 bool operator>(const NumberWithUnits& nwu_a,const NumberWithUnits& nwu_b){
   bool answer=false;
   if (nwu_a.number > convert_unit(nwu_b.number,nwu_b.unit,nwu_a.unit ))
    {answer = true;}
   return answer;
 }

 bool operator<(const NumberWithUnits& nwu_a,const NumberWithUnits& nwu_b){
   bool answer=false;
   if (nwu_a.number < convert_unit(nwu_b.number,nwu_b.unit,nwu_a.unit ))
    {answer = true;}
    return answer;
 }


 bool operator>=(const NumberWithUnits& nwu_a,const NumberWithUnits& nwu_b){
   bool answer=false;
   if ( nwu_a > nwu_b || nwu_a == nwu_b )
    {answer = true;}
   return answer;
 }

 bool operator<=(const NumberWithUnits& nwu_a,const NumberWithUnits& nwu_b){
   bool answer=false;
   if (nwu_a < nwu_b || nwu_a == nwu_b )
    {answer = true;}
    return answer;
 }

NumberWithUnits& operator+=(NumberWithUnits& nwu_a, const NumberWithUnits& nwu_b)
{
  nwu_a.number += convert_unit(nwu_b.number,nwu_b.unit,nwu_a.unit);
   return nwu_a;
}

NumberWithUnits& operator-=(NumberWithUnits& nwu_a, const NumberWithUnits& nwu_b)
{
  nwu_a.number -= convert_unit(nwu_b.number,nwu_b.unit,nwu_a.unit);
   return nwu_a;
}

NumberWithUnits operator+=(const NumberWithUnits& nwu_a, const NumberWithUnits& nwu_b)
{
   return  {nwu_a.number + convert_unit(nwu_b.number,nwu_b.unit,nwu_a.unit), nwu_a.unit};
}

NumberWithUnits operator-=(const NumberWithUnits& nwu_a, const NumberWithUnits& nwu_b)
{
   return  {nwu_a.number - convert_unit(nwu_b.number,nwu_b.unit,nwu_a.unit), nwu_a.unit};
}
}


