#include <iostream>
#include <stdio.h>
#include "PhysicalNumber.h"
#include "Unit.h"
using namespace std;
using namespace ariel;

namespace ariel{

    PhysicalNumber::PhysicalNumber(double _number, Unit _type){
        this->number = _number;
        this->type = _type;
    }
    
    const PhysicalNumber& PhysicalNumber::operator+= (const PhysicalNumber& num){
        return *this;
    }
    const PhysicalNumber& PhysicalNumber::operator-= (const PhysicalNumber& num){
        return *this;
    }
    
    PhysicalNumber PhysicalNumber::operator+ (const PhysicalNumber& num){
        // return PhysicalNumber(this->number, this->type);
        return *this;
    }
    PhysicalNumber PhysicalNumber::operator- (const PhysicalNumber& num){
        return *this;
    }
    
    const PhysicalNumber PhysicalNumber::operator- () const{
        return *this;
    } 
    const PhysicalNumber PhysicalNumber::operator+ () const{
        return *this;
    }
    
    PhysicalNumber& PhysicalNumber::operator++ () {
        return *this;
    }
    const PhysicalNumber PhysicalNumber::operator++ (int) {
        return *this;
    }
    PhysicalNumber& PhysicalNumber::operator-- () {
        return *this;
    }
    const PhysicalNumber PhysicalNumber::operator-- (int) {
        return *this;
    }
    
    bool operator>=(const PhysicalNumber& left, const PhysicalNumber& right){
        return true;
    } 
    bool operator==(const PhysicalNumber& left, const PhysicalNumber& right){
        return true;
    }
    bool operator!=(const PhysicalNumber& left, const PhysicalNumber& right){
        return true;
    }
    bool operator<(const PhysicalNumber& left, const PhysicalNumber& right){
        return true;
    }
    bool operator>(const PhysicalNumber& left, const PhysicalNumber& right){
        return true;
    }
    bool operator<=(const PhysicalNumber& left, const PhysicalNumber& right){
        return true;
    }
    
    std::ostream& operator<<(ostream& os, const PhysicalNumber& num){
        return os;
    }
    std::istream& operator>>(istream& is, const PhysicalNumber& num){
        return is;
    }

};
