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

    double PhysicalNumber::getNumber(){
        return this->number;
    }

    //checks if from the same dimension, if not throws exception
    void PhysicalNumber::sameDimension(const PhysicalNumber &num) const{

        int unit1 = (int)this->type % 3;
        int unit2 = (int)num.type % 3;

        if(unit1 != unit2){
            throw string("Physical numbers are not from the same dimension.");
        }
    
    }

    int PhysicalNumber::coefficientConvert(Unit type2){
    double coefficient=1;
    int dimension =(int)this->type % 3;  

    //if this the same type do not need conversion
    if((int)this->type == (int)type2){
        return coefficient;
    }

     switch (dimension)
     {
         //Length dimention
         case 0:
         if(type2 == Unit::CM && this->type == Unit::M) { coefficient = 0.01;  }    //cm to m
         if(type2 == Unit::CM && this->type == Unit::KM) { coefficient = 0.00001; } //cm to km
         if(type2 == Unit::M && this->type == Unit::CM) { coefficient = 100; }      //m to cm
         if(type2 == Unit::M && this->type == Unit::KM) { coefficient = 0.001; }    //m to km
         if(type2 == Unit::KM && this->type == Unit::CM) { coefficient = 10000; }   //km to cm
         if(type2 == Unit::KM && this->type == Unit::M) { coefficient = 1000; }     //km to m
             break;
        //Time dimention
         case 1:
         if(type2 == Unit::SEC && this->type == Unit::MIN) { coefficient = 0.0166667; }
         if(type2 == Unit::SEC && this->type == Unit::HOUR) { coefficient = 0.000277778; }
         if(type2 == Unit::MIN && this->type == Unit::SEC) { coefficient = 60; }
         if(type2 == Unit::MIN && this->type == Unit::HOUR) { coefficient = 0.0166667; }
         if(type2 == Unit::HOUR && this->type == Unit::SEC) { coefficient = 3600; }
         if(type2 == Unit::HOUR && this->type == Unit::MIN) { coefficient = 60; }
             break;
        //Weight dimention
         case 2:
         if(type2 == Unit::G && this->type == Unit::KG) { coefficient = 0.001;  }
         if(type2 == Unit::G && this->type == Unit::TON) { coefficient = 0.000001; }
         if(type2 == Unit::KG && this->type == Unit::G) { coefficient = 1000; }
         if(type2 == Unit::KG && this->type == Unit::TON) { coefficient = 0.001; }
         if(type2 == Unit::TON && this->type == Unit::G) { coefficient = 1000000; }
         if(type2 == Unit::TON && this->type == Unit::KG) { coefficient = 1000; }
             break;
     
         default:
             break;
     }  

     return coefficient; 
    }

    const PhysicalNumber convert(int convert,const PhysicalNumber& num){
        //to do//

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


