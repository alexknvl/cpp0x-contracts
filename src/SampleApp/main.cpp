#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <CppContracts/contracts.hpp>

template<class T>
class PositiveNumber {
public:
  PositiveNumber(T k) {
    requires(k > 0);
    value = k;
    ensures(value > 0);
  }
  
  T operator T() {
    return value;
  }
  
private:
  T value
};

double MySqrt(double v) {
  requires(v > 0);
  return v;
}

int main(int argc, char** argv) {
  try {
    PositiveNumber v(1);
  } catch(AssertionFailed& e) {
    printf("%s\n", e.what());
  }
  
  try {
    PositiveNumber v(-2);
  } catch(AssertionFailed& e) {
    printf("%s\n", e.what());
  }
  
  try {
    MySqrt(-1);
  } catch(AssertionFailed& e) {
    printf("%s\n", e.what());
  }
  
  try {
    assert(1 == 0);
  } catch(AssertionFailed& e) {
    printf("%s\n", e.what());
  }
  
  try {
    assertThrows(MySqrt(-1), std::string&);
  } catch(AssertionFailed& e) {
    printf("%s\n", e.what());
  }
}