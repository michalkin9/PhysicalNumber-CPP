#include <iostream>
#include <stdio.h>
#include <stdexcept>
#include "PhysicalNumber.h"
#include "Unit.h"
using namespace std;
using namespace ariel;



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
    // calcluate the coeff that needed to multiply with other number in order to get to the same type.
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
         if(type2 == Unit::KM && this->type == Unit::CM) { coefficient = 100000; }   //km to cm
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
     PhysicalNumber PhysicalNumber::convert(double convert,const PhysicalNumber& num) const{
        Unit new_unit = this->type;
        double new_number = num.number * convert;

        return PhysicalNumber(new_number,new_unit); 
    }
    
     PhysicalNumber& PhysicalNumber::operator+= (const PhysicalNumber& other){ 
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

     PhysicalNumber& PhysicalNumber::operator-= (const PhysicalNumber& other){ //works!
        if(sameDimension(other)){
            double coef = this->coefficientConvert(other.getUnit());
            PhysicalNumber sameUnit = this->convert(coef, other);
            double firstVal = this->getNumber();
            double secondVal = sameUnit.getNumber(); // conv to default Unit.
            double res = (firstVal - secondVal); // convert to the result unit
            this->setNumber(res);
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
    
     PhysicalNumber PhysicalNumber::operator- ()const { 
        double newNum = this->getNumber();
        newNum *= (-1);
        return PhysicalNumber(newNum,this->type);
    }
    
    PhysicalNumber PhysicalNumber::operator+ () const{ 
        return *this;
    }
    
    //prefix :: (++num)
    //          The prefix function increments the count, and returns this object by reference
    PhysicalNumber& PhysicalNumber::operator++ () {
        double newNum = this->getNumber();
        this->setNumber(++newNum);
        return *this;
    }
    
    //postfix :: (num++)
    //           The postfix function saves the old value 
    //           (by constructing a new instance with this object via the copy constructor),
    //           increments the count, and return the saved object by value.
     PhysicalNumber PhysicalNumber::operator++ (int) {
        PhysicalNumber res(this->getNumber(), this->getUnit());
        double newNum = this->getNumber();
         this->number++;
        return res;
    }
     /**
    Since both prefix and postfix operators are unary, a dummy int argument is assigned to postfix operator++()
    to distinguish it from prefix operator++().
    The prefix operator returns a reference to this object, but the postfix returns a value.
    ***/

    //prefix :: (++num)
    //          The prefix function decrements the count, and returns this object by reference
    PhysicalNumber& PhysicalNumber::operator-- () { //works!
        double newNum = this->getNumber();
        this->setNumber(--newNum);
        return *this;
    }
    
    //postfix :: (num--)
    //           The postfix function saves the old value 
    //           (by constructing a new instance with this object via the copy constructor),
    //           increments the count, and return the saved object by value.
    PhysicalNumber PhysicalNumber::operator-- (int) { //works!
        PhysicalNumber res(this->getNumber(), this->getUnit());
        double newNum = this->getNumber();
       this->number--;
        return res;
    }

    /**
    Since both prefix and postfix operators are unary, a dummy int argument is assigned to postfix operator++() 
    to distinguish it from prefix operator++().
    The prefix operator returns a reference to this object, but the postfix returns a value.
    ***/
    
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
    bool PhysicalNumber::operator!=(const PhysicalNumber& right) const{
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
    
    std::ostream& ariel::operator<<(ostream& os, const PhysicalNumber& num){
        string strType;
        switch(num.type){
            case Unit::CM: strType = "[cm]"; break;
            case Unit::SEC: strType = "[sec]"; break;
            case Unit::G: strType = "[g]"; break;
            case Unit::M: strType = "[m]"; break;
            case Unit::MIN: strType = "[min]"; break;
            case Unit::KG: strType = "[kg]"; break;
            case Unit::KM: strType = "[km]"; break;
            case Unit::HOUR: strType = "[hour]"; break;
            case Unit::TON: strType = "[ton]"; break;
        }
        return os << num.number << strType;
    }
    bool isNumber(const string& s) {
	    bool dot = false;
    	    if(s.size()==0) return false;
            for(int i=0;i<s.size();i++) {
		if(!dot && s[i] == '.'){
		    dot = true;
		    continue;
		}
		if((s[i]>='0' && s[i]<='9')==false) {
		    return false;
		}
    	    }
    	    return true;
    }
    
    std::istream& ariel::operator>>(istream& is, PhysicalNumber& num){
        string input;
        double newNum = 0;
        string _value;
        is >> input;

        int foundStart = input.find("[");
        
        _value = input.substr(0, foundStart);
        
        if(foundStart <= 0 || !isNumber(_value)){
            is.setstate(std::ios::badbit); // Error due to the failure of an input/output operation on the stream buffer.
            is.clear(); // This will clear all the stream error state from std::cin.
            return is;
        }
        
        if (input.find("[cm]") != -1){ // if found
            num.setUnit(Unit::CM);
        }
        else if (input.find("[sec]") != -1){
            num.setUnit(Unit::SEC);
        }
        else if (input.find("[g]") != -1){
            num.setUnit(Unit::G);
        }
        else if (input.find("[m]") != -1){
            num.setUnit(Unit::M);
        }
        else if (input.find("[min]") != -1){
            num.setUnit(Unit::MIN);
        }
        else if (input.find("[kg]") != -1){
            num.setUnit(Unit::KG);
        }
        else if (input.find("[km]") != -1){
            num.setUnit(Unit::KM);
        }
        else if (input.find("[hour]") != -1){
            num.setUnit(Unit::HOUR);
        }
        else if (input.find("[ton]") != -1){
            num.setUnit(Unit::TON);
        }
        else{
            is.setstate(std::ios::badbit); // Error due to the failure of an input/output operation on the stream buffer.
            return is;
        }
        
        try{
            newNum = std::stod(_value); //convert string into double
        }catch(std::exception& e){
            is.setstate(std::ios::badbit);
            is.clear();
            return is;
        }
        
        num.setNumber(newNum);
        return is;

    }
    
    void PhysicalNumber::error() const{
        throw runtime_error("PhysicalNumbers are not from the same dimension.");
    }
