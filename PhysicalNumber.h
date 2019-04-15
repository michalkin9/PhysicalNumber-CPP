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
            PhysicalNumber(double num ,Unit unit); //to impliment here
            
            double getNumber() const;
            Unit getUnit() const;
            void setNumber(const double number);
            void setUnit(const Unit _type);
            
            friend std::ostream& operator<<(ostream& os, const PhysicalNumber& num);
            friend std::istream& operator>>(istream& os, const PhysicalNumber& num);
    
            const PhysicalNumber operator- (); //unarys
            const PhysicalNumber operator+ () const;
    
            PhysicalNumber& operator++ () ; //prefix(++num)
            const PhysicalNumber operator++ (int) ; //postfix(num++)
    
            PhysicalNumber& operator-- () ; //prefix(++num)
            const PhysicalNumber operator-- (int) ; //postfix(num++)
    
            const PhysicalNumber& operator+= (const PhysicalNumber& num);
            const PhysicalNumber& operator-= (const PhysicalNumber& num);
    
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
            const PhysicalNumber convert(double convert,const PhysicalNumber& num);
            void error() const;

    };

}