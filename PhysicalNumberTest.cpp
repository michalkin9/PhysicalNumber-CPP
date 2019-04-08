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
    PhysicalNumber time4(10,Unit::SEC);

    PhysicalNumber dist1(1,Unit::KM);
    PhysicalNumber dist2(500,Unit::M);
    PhysicalNumber dist3(1,Unit::M);
    PhysicalNumber dist4(10,Unit::CM);

    PhysicalNumber weight1(200, Unit::G);
    PhysicalNumber weight2(1, Unit::KG);
    PhysicalNumber weight3(4, Unit::TON);
    PhysicalNumber weight4(0.1, Unit::TON);

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
    .CHECK_OUTPUT(time1+time2, "2.3[hour]")
    .CHECK_OUTPUT(weight2-weight2, "[km]")
    .CHECK_OUTPUT(b-b, "0[m]")
    .CHECK_OUTPUT(c, "2[hour]")
    .CHECK_OUTPUT(d, "30[min]")
    .CHECK_OUTPUT(d+c, "150[min]")


    


















































      .print(cout, /*show_grade=*/false);
      grade = testcase.grade();
    } else {
      testcase.print_signal(signal);
      grade = 0;
    }
    cout <<  "*** Grade: " << grade << " ***" << endl;
    return grade;
}