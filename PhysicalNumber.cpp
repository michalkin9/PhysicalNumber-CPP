#include <iostream>
#include <stdio.h>
#include <stdexcept>
#include "PhysicalNumber.h"
#include "Unit.h"
using namespace std;
using namespace ariel;

namespace ariel{

    Unit PhysicalNumber::getUnit() const{
        return type;
    }
    
    double PhysicalNumber::getNumber() const {
        return number;
    }
            
    void PhysicalNumber::setNumber(const double _number){
		this->number = _number; 
    }
    
    void PhysicalNumber::setUnit(const Unit _type){
		this->type = _type; 
    }

    PhysicalNumber::PhysicalNumber(double _number, Unit _type){
        this->number = _number;
        this->type = _type;
    }
    
    //checks if from the same dimension, if not throws exception
    bool PhysicalNumber::sameDimension(const PhysicalNumber &num) const{

        int unit1 = (int)this->type % 3;
        int unit2 = (int)num.type % 3;

        if(unit1 != unit2){
            return false;
        }
        return true;
    
    }
    
    double PhysicalNumber::coefficientConvert(const Unit type2)const{
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
         if(type2 == Unit::SEC && this->type == Unit::MIN) { coefficient = 0.0166667; }     //sec to min
         if(type2 == Unit::SEC && this->type == Unit::HOUR) { coefficient = 0.000277778; }  //sec to hour
         if(type2 == Unit::MIN && this->type == Unit::SEC) { coefficient = 60; }            //min to sec
         if(type2 == Unit::MIN && this->type == Unit::HOUR) { coefficient = 0.0166667; }    //min to hour
         if(type2 == Unit::HOUR && this->type == Unit::SEC) { coefficient = 3600; }         //hour to sec
         if(type2 == Unit::HOUR && this->type == Unit::MIN) { coefficient = 60; }           //hour to min
             break;
        //Weight dimention
         case 2:
         if(type2 == Unit::G && this->type == Unit::KG) { coefficient = 0.001;  }       //gr to kg       
         if(type2 == Unit::G && this->type == Unit::TON) { coefficient = 0.000001; }    //gr to ton
         if(type2 == Unit::KG && this->type == Unit::G) { coefficient = 1000; }         //kg to gr
         if(type2 == Unit::KG && this->type == Unit::TON) { coefficient = 0.001; }      //kg to ton
         if(type2 == Unit::TON && this->type == Unit::G) { coefficient = 1000000; }     //ton to gr
         if(type2 == Unit::TON && this->type == Unit::KG) { coefficient = 1000; }       //ton to kg
             break;
     
         default:
             break;
     }  

     return coefficient; 
    }

    //gets the coeffiecnt convert and the PhysicalNumber that need to be convert - returns new one
    const PhysicalNumber PhysicalNumber::convert(double convert,const PhysicalNumber& num){
        Unit new_unit = this->type;
        double new_number = num.number * convert;

        return PhysicalNumber(new_number,new_unit); 
    }
    
    const PhysicalNumber& PhysicalNumber::operator+= (const PhysicalNumber& other){ // ****************new*********************
        if(this->sameDimension(other)){
            double coef = this->coefficientConvert(other.getUnit());
            PhysicalNumber sameUnit = this->convert(coef, other);
            double firstVal = this->getNumber();
            double secondVal = sameUnit.getNumber(); // conv to default Unit.
            double res = (firstVal + secondVal); // convert to the result unit
            this->setNumber(res);
            //PhysicalNumber result(res, resultUnit);
            return *this;
        }
        else error();
    }

    const PhysicalNumber& PhysicalNumber::operator-= (const PhysicalNumber& other){ //works!
        if(sameDimension(other)){
            double coef = this->coefficientConvert(other.getUnit());
            PhysicalNumber sameUnit = this->convert(coef, other);
            double firstVal = this->getNumber();
            double secondVal = sameUnit.getNumber(); // conv to default Unit.
            double res = (firstVal - secondVal); // convert to the result unit
            this->setNumber(res);
            //PhysicalNumber result(res, resultUnit);
            return *this;
        }
        else error();
    }
    
    PhysicalNumber PhysicalNumber::operator+ (const PhysicalNumber& other){ //works!
        if(!sameDimension(other)){
            error();
        }
        else{
            double coef = this->coefficientConvert(other.getUnit());
            PhysicalNumber sameUnit = this->convert(coef, other);
            double firstVal = this->getNumber(); // calculate on the same type
            double secondVal = sameUnit.getNumber(); // calculate on the same type
            double res = (firstVal + secondVal); // back to unit we want
            PhysicalNumber newNum(res, sameUnit.getUnit()); // creates new object
            return newNum;
            
        }
    }
    
    PhysicalNumber PhysicalNumber::operator- (const PhysicalNumber& other){ //works!
        if(!sameDimension(other)){
            error();
        }
        else{
            double coef = this->coefficientConvert(other.getUnit());
            PhysicalNumber sameUnit = this->convert(coef, other);
            double firstVal = this->getNumber(); // calculate on the same type
            double secondVal = sameUnit.getNumber(); // calculate on the same type
            double res = (firstVal - secondVal); // back to unit we want
            PhysicalNumber newNum(res, sameUnit.getUnit()); // creates new object
            return newNum;
            
        }
    }
    
    const PhysicalNumber PhysicalNumber::operator- (){ //works!
        double newNum = this->getNumber();
        newNum *= (-1);
        this->setNumber(newNum);
        return *this;
    }
    
    const PhysicalNumber PhysicalNumber::operator+ () const{ //works!
        return *this;
    }
    
    PhysicalNumber& PhysicalNumber::operator++ () { // works!
        double newNum = this->getNumber();
        this->setNumber(++newNum);
        return *this;
    }
    
    const PhysicalNumber PhysicalNumber::operator++ (int) { // works!
        PhysicalNumber res(this->getNumber(), this->getUnit());
        double newNum = this->getNumber();
        ++newNum;
        this->setNumber(newNum);
        return res;
    }
    
    PhysicalNumber& PhysicalNumber::operator-- () { //works!
        double newNum = this->getNumber();
        this->setNumber(--newNum);
        return *this;
    }
    
    const PhysicalNumber PhysicalNumber::operator-- (int) { //works!
        PhysicalNumber res(this->getNumber(), this->getUnit());
        double newNum = this->getNumber();
        --newNum;
        res.setNumber(newNum);
        return res;
    }
    
    bool PhysicalNumber::operator>=(const PhysicalNumber& right)const{ 
        if(!sameDimension(right)){
            error();
        }
        else{
            double coef = this->coefficientConvert(right.getUnit());
            double compNumber = right.number * coef;
            return (!(this->number < compNumber))  ? true : false;
        }
    }
    bool PhysicalNumber::operator==(const PhysicalNumber& right)const{
        if(!sameDimension(right)){
            error();
        }
        else{
            double coef = this->coefficientConvert(right.getUnit());
            double compNumber = right.number * coef;
            return (this->number == compNumber)  ? true : false;
        }
    }
    bool PhysicalNumber::operator!=(const PhysicalNumber& right)const{
         if(!sameDimension(right)){
            error();
        }
        else{
            double coef = this->coefficientConvert(right.getUnit());
            double compNumber = right.number * coef;
            return (this->number < compNumber) || (this->number > compNumber)  ? true : false;
        }
    }
    bool PhysicalNumber::operator<(const PhysicalNumber& right)const{
         if(!sameDimension(right)){
            error();
        }
        else{
            double coef = this->coefficientConvert(right.getUnit());
            double compNumber = right.number * coef;
            return this->number < compNumber ? true : false;
        }
    }
    bool PhysicalNumber::operator>(const PhysicalNumber& right)const{
        if(!sameDimension(right)){
            error();
        }
        else{
            double coef = this->coefficientConvert(right.getUnit());
            double compNumber = right.number * coef;
            return this->number < compNumber ? false : true;
        }
    }
    
    bool PhysicalNumber::operator<=(const PhysicalNumber& right)const{
        if(!sameDimension(right)){
            error();
        }
        else{
            double coef = this->coefficientConvert(right.getUnit());
            double compNumber = right.number * coef;
            return (!(this->number > compNumber))  ? true : false;
        }
    }
    
    std::ostream& operator<<(ostream& os, const PhysicalNumber& num){
        return os;
    }
    std::istream& operator>>(istream& is, const PhysicalNumber& num){
        return is;
    }
    
    void PhysicalNumber::error() const{
        throw runtime_error("PhysicalNumbers are not from the same dimension.");
    }
};

    int main() {
        PhysicalNumber num1(60,Unit::SEC);
        PhysicalNumber num2(1, Unit::MIN);
        bool value = (num2 == num1);
        std::cout << value << endl;
        
        return 0;
    }