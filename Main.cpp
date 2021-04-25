/**
 * Demo file for the exercise on numbers with units
 *
 * @author Erel Segal-Halevi
 * @since 2019-02
 */
// #include "doctest.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cfloat>
#include <limits>
using namespace std;
#include "NumberWithUnits.hpp"
using namespace ariel;

int main() {
    ofstream myfile;
    myfile.open ("myTestFile.txt");
    myfile << "1 km = 1000 m" << endl;
    myfile << "1 m = 100 cm" << endl;
    myfile << "1 kg = 1000 g" << endl;
    myfile << "1 ton = 1000 kg" << endl;
    myfile << "1 hour = 60 min" << endl;
    myfile << "1 min = 60 sec" << endl;
    myfile << "1 day = 24 hour" << endl;
    myfile << "1 month = 30 day" << endl;
    myfile << "1 year = 12 month" << endl;   
    myfile.close(); 
    ifstream units_file{"myTestFile.txt"};
    NumberWithUnits::read_units(units_file);

    //////////////////////////////////////////////////////// operators '==' , '>=' , '<=' ////////////////////////////////////////////////
    //     NumberWithUnits ton_1(1 , "ton");
    // NumberWithUnits kg_1000(1000 , "kg");
    // NumberWithUnits g_1000000(1000000 , "g");
    // NumberWithUnits mg_1000000000(1000000000 , "mg");
      NumberWithUnits sec100=NumberWithUnits(100,"sec");
    NumberWithUnits day1=NumberWithUnits(1,"day");
    cout << boolalpha;
    cout << (day1-sec100) ;
    cout << "\n" << (1-100.0/(60*60*24));

    // cout << "\n" << mg_1000000000 << "\n" ;
    // cout << "\n" << ton_1 << "\n";
    // cout << (ton_1 == mg_1000000000);





  return 0;
}
