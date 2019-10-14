#include "RPNCalculator.h"

const double EPS = 1E-8;

TEST_CASE("Digit computes correctly") {
  RPNCalculator rc;
  CHECK_EQ(rc.calculateRPN("9"), doctest::Approx(9).epsilon(EPS));
}

TEST_CASE("Single addition computes correctly") {
  RPNCalculator rc;
  CHECK_EQ(rc.calculateRPN("23+"), doctest::Approx(5).epsilon(EPS));
}

TEST_CASE("Complex expression computes correctly") {
  RPNCalculator rc;
  CHECK_EQ(rc.calculateRPN("12+345/-*"), doctest::Approx(6.6).epsilon(EPS));
}

TEST_CASE("Digit converts correctly") {
  RPNCalculator rc;
  CHECK_EQ(rc.toRPN("9"), "9");
}

TEST_CASE("Single addition converts correctly") {
  RPNCalculator rc;
  CHECK_EQ(rc.toRPN("2+3"), "23+");
}

TEST_CASE("Complex expression converts correctly") {
  RPNCalculator rc;
  CHECK_EQ(rc.toRPN("(1+2)*(3-4/5)"), "12+345/-*");
}

TEST_CASE("Viktor's expression converts correctly") {
  RPNCalculator rc;
  CHECK_EQ(rc.toRPN("(((1*3)+4-5))"), "13*4+5-");
}

TEST_CASE("Expression where priority matters computes correctly") {
  RPNCalculator rc;
  CHECK_EQ(rc.calculate("(1+2)*(3/4-5)"), doctest::Approx(-12.75).epsilon(EPS));
}

TEST_CASE("Viktor's expression computes correctly") {
  RPNCalculator rc;
  CHECK_EQ(rc.calculate("(((1*3)+4-5))"), doctest::Approx(2).epsilon(EPS));
}

TEST_CASE("Trifon's revision of Viktor's expression computes correctly") {
  RPNCalculator rc;
  CHECK_EQ(rc.calculate("(((1*3)-4-5))"), doctest::Approx(-6).epsilon(EPS));
}
