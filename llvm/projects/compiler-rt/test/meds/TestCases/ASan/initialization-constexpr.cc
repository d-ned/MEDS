// Constexpr:
// We need to check that a global variable initialized with a constexpr
// constructor can be accessed during dynamic initialization (as a constexpr
// constructor implies that it was initialized during constant initialization,
// not dynamic initialization).

// RUN: %clangxx_meds -O0 %s %p/Helpers/initialization-constexpr-extra.cc --std=c++11 -o %t
// RUN: %env_asan_opts=check_initialization_order=true %run %t 2>&1
// RUN: %clangxx_meds -O1 %s %p/Helpers/initialization-constexpr-extra.cc --std=c++11 -o %t
// RUN: %env_asan_opts=check_initialization_order=true %run %t 2>&1
// RUN: %clangxx_meds -O2 %s %p/Helpers/initialization-constexpr-extra.cc --std=c++11 -o %t
// RUN: %env_asan_opts=check_initialization_order=true %run %t 2>&1
// RUN: %clangxx_meds -O3 %s %p/Helpers/initialization-constexpr-extra.cc --std=c++11 -o %t
// RUN: %env_asan_opts=check_initialization_order=true %run %t 2>&1

class Integer {
  private:
  int value;

  public:
  constexpr Integer(int x = 0) : value(x) {}
  int getValue() {return value;}
};
Integer coolestInteger(42);
int getCoolestInteger() { return coolestInteger.getValue(); }

int main() { return 0; }
