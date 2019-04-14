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
            PhysicalNumber(double num ,Unit unit); 
            Unit getUnit();
            double getNumber();

            friend std::ostream& operator<<(ostream& os, const PhysicalNumber& num);
            friend std::istream& operator>>(istream& os, const PhysicalNumber& num);
    
            const PhysicalNumber operator- () const; //unarys
            const PhysicalNumber operator+ () const;
    
            PhysicalNumber& operator++ () ; //prefix(++num)
            const PhysicalNumber operator++ (int) ; //postfix(num++)
    
            PhysicalNumber& operator-- () ; //prefix(++num)
            const PhysicalNumber operator-- (int) ; //postfix(num++)
    
            const PhysicalNumber& operator+= (const PhysicalNumber& num);
            const PhysicalNumber& operator-= (const PhysicalNumber& num);
    
            PhysicalNumber operator+(const PhysicalNumber& num1);
            PhysicalNumber operator-(const PhysicalNumber& num1);
    
            friend bool operator==(const PhysicalNumber& left, const PhysicalNumber& right);
            friend bool operator!=(const PhysicalNumber& left, const PhysicalNumber& right);
            friend bool operator<(const PhysicalNumber& left, const PhysicalNumber& right);
            friend bool operator>(const PhysicalNumber& left, const PhysicalNumber& right);
            friend bool operator>=(const PhysicalNumber& left, const PhysicalNumber& right);
            friend bool operator<=(const PhysicalNumber& left, const PhysicalNumber& right);   
            
            private:
            void sameDimension(const PhysicalNumber& num)const;
            double coefficientConvert(Unit type2);
            const PhysicalNumber convert(double convert,const PhysicalNumber& num);


    };


}