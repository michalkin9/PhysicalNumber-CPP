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

    Unit PhysicalNumber::getUnit(){
    return this->type;
    }

    //checks if from the same dimension, if not throws exception
    void PhysicalNumber::sameDimension(const PhysicalNumber &num) const{

        int unit1 = (int)this->type % 3;
        int unit2 = (int)num.type % 3;

        if(unit1 != unit2){
            throw string("Physical numbers are not from the same dimension.");
        }
    
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


