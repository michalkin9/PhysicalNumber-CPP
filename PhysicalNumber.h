#pragma once
using namespace std;

#include "Unit.h"
#include <iostream>
#include <stdlib.h> // if we will use 

namespace ariel{

    class PhysicalNumber{

        private:
            double number;
            Unit type;
        
        public:
            //Constructor:
            PhysicalNumber(double num ,Unit unit); 
            
            double getNumber() const;
            Unit getUnit() const;
            void setNumber(const double number);
            void setUnit(const Unit _type);
            
            //streams:
            friend ostream& operator<<(ostream& os, const PhysicalNumber& num);
            friend istream& operator>>(istream& os,  PhysicalNumber& num);
            
            //unarys:
            PhysicalNumber operator- ()const ; 
            PhysicalNumber operator+ () const;
    
            PhysicalNumber& operator++ () ; //prefix(++num)
            PhysicalNumber operator++ (int) ; //postfix(num++)
    
            PhysicalNumber& operator-- () ; //prefix(++num)
            PhysicalNumber operator-- (int) ; //postfix(num++)
    
            PhysicalNumber& operator+= (const PhysicalNumber& num);
            PhysicalNumber& operator-= (const PhysicalNumber& num);
    
            PhysicalNumber operator+(const PhysicalNumber& num1);
            PhysicalNumber operator-(const PhysicalNumber& num1);
            
    
            bool operator==(const PhysicalNumber& right)const;
            bool operator!=(const PhysicalNumber& right)const;
            bool operator< (const PhysicalNumber& right)const;
            bool operator>(const PhysicalNumber& right)const;
            bool operator>=(const PhysicalNumber& right)const;
            bool operator<=(const PhysicalNumber& right)const;

        private:
            bool sameDimension(const PhysicalNumber& num)const;
            double coefficientConvert(const Unit type2)const;
            PhysicalNumber convert(double convert,const PhysicalNumber& num)const;
            void error() const;
            bool isNumber(const string& s);

    };

}
