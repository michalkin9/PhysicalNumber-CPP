/**
 * Examples of automatic tests for the exercise on physical numbers.
 *
 * @author Erel Segal-Halevi
 * @since 2019-02
 */

#include <iostream>
#include <sstream>
using std::cout, std::endl, std::istringstream;
#include "PhysicalNumber.h"
using ariel::PhysicalNumber, ariel::Unit;
#include "badkan.hpp"

int main() {
  badkan::TestCase testcase;
  int grade=0;
  int signal = setjmp(badkan::longjmp_buffer);
  if (signal == 0) {

    // BASIC TESTS - DO NOT CHANGE
    PhysicalNumber a(2, Unit::KM);
    PhysicalNumber b(300, Unit::M);
    PhysicalNumber c(2, Unit::HOUR);
    PhysicalNumber d(30, Unit::MIN);

    PhysicalNumber time1(2,Unit::HOUR);
    PhysicalNumber time2(20,Unit::MIN);
    PhysicalNumber time3(1,Unit::MIN);
    PhysicalNumber time4(60,Unit::SEC);
	PhysicalNumber time5(60,Unit::MIN);

    PhysicalNumber dist1(1,Unit::KM);
    PhysicalNumber dist2(500,Unit::M);
    PhysicalNumber dist3(1,Unit::M);
    PhysicalNumber dist4(10,Unit::CM);

    PhysicalNumber weight1(200, Unit::G);
    PhysicalNumber weight2(1, Unit::KG);
    PhysicalNumber weight3(4, Unit::TON);
    PhysicalNumber weight4(0.1, Unit::TON);
	
	PhysicalNumber num1(50, Unit::MIN);
	PhysicalNumber num2(12, Unit::KM);
	PhysicalNumber num3(1, Unit::TON);

    testcase
    .setname("Basic output")
    .CHECK_OUTPUT(a, "2[km]")
    .CHECK_OUTPUT(b, "300[m]")

    .setname("Compatible dimensions")
    .CHECK_OUTPUT(b+a, "2300[m]")
    .CHECK_OUTPUT((a+=b), "2.3[km]")
    .CHECK_OUTPUT(a, "2.3[km]")
    .CHECK_OUTPUT(a+a, "4.6[km]")
    .CHECK_OUTPUT(b-b, "0[m]")
    .CHECK_OUTPUT(c, "2[hour]")
    .CHECK_OUTPUT(d, "30[min]")
    .CHECK_OUTPUT(d+c, "150[min]")

    .setname("Incompatible dimensions")
    .CHECK_THROWS(a+c)
    .CHECK_THROWS(a+d)
    .CHECK_THROWS(b+c)
    .CHECK_THROWS(b+d)

    .setname("Basic input")
    .CHECK_OK(istringstream("700[kg]") >> a)
    .CHECK_OUTPUT((a += PhysicalNumber(1, Unit::TON)), "1700[kg]")

    // Our Tests

    .setname("The operator '+' binary - Incompatible dimensions")
    .CHECK_THROWS(time1+dist1)
    .CHECK_THROWS(dist2+weight3)
    .CHECK_THROWS(weight2+time3)

    .setname("The operator '-' binary - Incompatible dimensions")
    .CHECK_THROWS(dist4-time2)
    .CHECK_THROWS(weight4-dist4)
    .CHECK_THROWS(time3-weight1)

    .setname("The operator '+' binary - compatible dimensions")
    .CHECK_OUTPUT(time2+time1, "140[min]")
    .CHECK_OUTPUT(time2+time3, "21[min]")
    .CHECK_OUTPUT(time1+time2, "2.33333[hour]")//?
    .CHECK_OUTPUT(weight1+weight2, "1200[g]")
    .CHECK_OUTPUT(weight2+weight3, "4001[kg]")
    .CHECK_OUTPUT(weight3+weight2, "4.001[ton]")
    .CHECK_OUTPUT(dist1+dist1, "2[km]")
	.CHECK_OUTPUT(dist1+dist2, "1.5[km]")
	.CHECK_OUTPUT(dist2+dist1, "1500[m]")
	.CHECK_OUTPUT(dist3+dist4, "1.1[m]")


    .setname("The operator '-' binary - compatible dimensions")
	.CHECK_OUTPUT(time3-time4, "0[min]")	
	.CHECK_OUTPUT(time2-time3, "19[min]")
	.CHECK_OUTPUT(time1-time5, "1[hour]")
	.CHECK_OUTPUT(dist1-dist2, "0.5[km]")
	.CHECK_OUTPUT(dist3-dist4, "0.9[m]")
	.CHECK_OUTPUT(dist2-dist3, "499[m]")
	.CHECK_OUTPUT(weight3-weight4, "3.9[ton]")
	.CHECK_OUTPUT(weight3-weight2, "3.999[ton]")
	.CHECK_OUTPUT(weight2-weight1, "0.8[kg]")
	
	.setname("Operator '+=' binary - Incompatible dimensions")
    .CHECK_THROWS((time1+=weight1))
    .CHECK_THROWS((weight2+=dist2))
    .CHECK_THROWS((dist3+=time2))
	
	.setname("The operator '-=' binary - Incompatible dimensions")
	.CHECK_THROWS((time1-=weight1))
    .CHECK_THROWS((weight2-=dist2))
    .CHECK_THROWS((dist3-=time2))
	
	.setname("Operator '+=' binary - Compatible dimensions")
	.CHECK_OUTPUT((time1+=time5), "3[hour]")
	.CHECK_OUTPUT((time3+=time4), "2[min]")
	.CHECK_OUTPUT((time3+=time2), "22[min]")
	.CHECK_OUTPUT((weight2+=weight1), "1.2[kg]")
	.CHECK_OUTPUT((weight3+=weight4), "4.1[ton]")
	.CHECK_OUTPUT((weight3+=weight2), "4.10132277[ton]")
	.CHECK_OUTPUT((dist1+=dist2), "1.5[km]")
	.CHECK_OUTPUT((dist4+=dist3), "110[cm]")
	.CHECK_OUTPUT((dist4+=dist1), "150110[cm]")
	

	.setname("The operator '-=' binary - Compatible dimensions")
	.CHECK_OUTPUT((dist4-=dist1), "110[cm]") 
	.CHECK_OUTPUT((dist4-=dist3), "10[cm]") 
	.CHECK_OUTPUT((dist1-=dist2), "1[km]")
	.CHECK_OUTPUT((weight3-=weight2), "4.1[ton]")
	.CHECK_OUTPUT((weight3-=weight4), "4[ton]")
	.CHECK_OUTPUT((weight2-=weight1), "1[kg]")
	.CHECK_OUTPUT((time3-=time2), "2[min]")
	.CHECK_OUTPUT((time3-=time4), "1[min]")
	.CHECK_OUTPUT((time1-=time5), "1[hour]")
	
	.setname("The operator '++(postfix)' unary - Compatible dimensions")
    .CHECK_OUTPUT(time1++,"3[hour]")                                       
    .CHECK_OUTPUT(dist2++,"501[m]")                                       
    .CHECK_OUTPUT(weight2++,"2[kg]")                                      
 
    .setname("Operator '--(postfix)' unary - Compatible dimensions")
    .CHECK_OUTPUT(time1--,"2[hour]")                                       
    .CHECK_OUTPUT(dist2--,"500[m]")                                       
    .CHECK_OUTPUT(weight2--,"1[kg]")                                      

	.setname("The operator '++(postfix)' unary - Compatible dimensions")
    .CHECK_OUTPUT(++time1,"3[hour]")                                       
    .CHECK_OUTPUT(++dist2,"501[m]")                                       
    .CHECK_OUTPUT(++weight2,"2[kg]")                                      
 
    .setname("Operator '--(postfix)' unary - Compatible dimensions")
    .CHECK_OUTPUT(--time1,"2[hour]")                                       
    .CHECK_OUTPUT(--dist2,"500[m]")                                       
    .CHECK_OUTPUT(--weight2,"1[kg]")
	
	.setname("Operator '-' unary - Compatible dimensions")
    .CHECK_EQUAL(-PhysicalNumber(5,Unit::TON),PhysicalNumber(-5,Unit::TON))
    .CHECK_EQUAL(PhysicalNumber(-10,Unit::CM),dist4 )   

	.setname("Operator '+' unary - Compatible dimensions")
    .CHECK_EQUAL(+dist1,dist1)
    .CHECK_EQUAL(PhysicalNumber(10,Unit::CM),+dist4 )	
	
	.setname("Operator '==','!=' binary - Incompatible dimensions")
    .CHECK_THROWS((dist1==time1))
    .CHECK_THROWS((weight1==dist1))
    .CHECK_THROWS((time3!=dist2))
    .CHECK_THROWS((dist2!=weight3))

    .setname("Operator '==' and '!=' binary - Compatible dimensions")                                        
    .CHECK_EQUAL((time2==PhysicalNumber(20,Unit::MIN)),true)                                             
    .CHECK_EQUAL(dist1==PhysicalNumber(1,Unit::KM),true)  
    .CHECK_EQUAL(dist3==dist2,false)
	.CHECK_EQUAL(time4==time4,true)
    .CHECK_EQUAL(weight1==PhysicalNumber(210,Unit::G),false)           
    .CHECK_EQUAL(time2!=time1,true)                                                                              
    .CHECK_EQUAL(dist3!=PhysicalNumber(2,Unit::M),true)   

    .setname("Operator '<=','>=' binary - Incompatible dimensions")
    .CHECK_THROWS(time1<=dist1)
    .CHECK_THROWS(weight3>=time2)
    .CHECK_THROWS(time1>=weight1)
    .CHECK_THROWS(dist2<=weight3)	
	
    .setname("Operator '<=' binary - Compatible dimensions")
    .CHECK_EQUAL(time2<=time1,true)                                       
    .CHECK_EQUAL(weight4<=weight3,true)  
	.CHECK_EQUAL(time1<=time4,false) 
    .CHECK_EQUAL(dist2<=dist1,true)   

    .setname("Operator '>=' binary - Compatible dimensions")
    .CHECK_EQUAL(time2>=time1,false)                                       
    .CHECK_EQUAL(weight4>=weight3,false)  
	.CHECK_EQUAL(time1>=time4,true) 
    .CHECK_EQUAL(dist2>=dist1,false)  	
	
	.setname("Operator '<=' binary - Compatible dimensions")
    .CHECK_EQUAL(time2<time1,true)                                       
    .CHECK_EQUAL(weight4<weight3,true)  
	.CHECK_EQUAL(time1<time4,false) 
    .CHECK_EQUAL(dist2<dist1,true)   

    .setname("Operator '>=' binary - Compatible dimensions")
    .CHECK_EQUAL(time2>time1,false)                                       
    .CHECK_EQUAL(weight4>weight3,false)  
	.CHECK_EQUAL(time1>time4,true) 
    .CHECK_EQUAL(dist2>dist1,false)  	
 
    .setname("Operator '<','>' binary - Incompatible dimensions")
    .CHECK_THROWS(time1<dist1)
    .CHECK_THROWS(weight3>time2)
    .CHECK_THROWS(time1>weight1)
    .CHECK_THROWS(dist2<weight3)	
	
	.setname("Input - Compatible dimensions")
    .CHECK_OK(istringstream("50[min]") >> num1)
    .CHECK_OUTPUT(num1,"50[min]")
    .CHECK_OK(istringstream("12[km]") >> num2)
    .CHECK_OUTPUT(num2,"12[km]")
    .CHECK_OK(istringstream("1[ton]") >> num3)
    .CHECK_OUTPUT(num3,"1[ton]")
	
    .setname("...")
	
	.print(cout, /*show_grade=*/false);
      grade = testcase.grade();
    } else {
      testcase.print_signal(signal);
      grade = 0;
    }
    cout <<  "*** Grade: " << grade << " ***" << endl;
    return grade;
}
	
	
	

	

