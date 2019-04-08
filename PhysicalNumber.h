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
            bool isValid(const PhysicalNumber a,const PhysicalNumber b); //to check if the unit is from the same dimantion

        public:
            PhysicalNumber(double num ,Unit unit); //to impliment here
            Unit getUnit(const string _type);
    
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


    };

 }