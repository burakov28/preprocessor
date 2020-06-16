#include "simple-definitions.h"

#include <iostream>
#include <vector>

std::vector<int> v = {
#include "test"
};

#define A 6
#define STR "abacaba"

#define EMPTY

#define puba push_back
#define ff first
#define ss second


void check_simple_definitions() {
  std::cout << A << std::endl;
  std::cout << STR << std::endl;
  #ifdef CMD
  std::cout << CMD << std::endl;
  #else
  std::cout << "NO CMD" << std::endl;
    #error Bad
  #endif

  #if defined(A) && A > 9
  std::cout << A << " defined and greater than 10" << std::endl;
  #elif defined(A) && A > 5
    #if defined(STR)
  std::cout << "Nested 'if' works!" << std::endl;
    #endif
  std::cout << A << " defined and greater than 5" << std::endl;
  #else
  std::cout << "A not defined or leq than 9" << std::endl;
  #endif

  #undef A
  // std::cout << A << std::endl;

  #ifdef EMPTY
  std::cout << "EMPTY defined" << std::endl;
  #endif

  #ifndef UNDEFINED
  std::cout << "UNDEFINED is undefined" << std::endl;
  #endif

  int aq = 10 +
          #ifdef CMD
          +100
          #endif
          +15;
  std::cout << aq << std::endl;

  srand(time(nullptr));
  std::vector<std::pair<int, int>> v;
  for (int i = 0; i < 10; ++i) {
    std::pair<int, int> a;
    a.ff = rand() % 10;
    a.ss = rand() % 200;
    v.puba(a);
  }



  ssize_t val = 10;
  std::cout << val << std::endl;
  std::string puba = "puba string";
  std::cout << push_back << std::endl;

  for (const auto &p : v) {
    std::cout << p.ff << " " << p.ss << "    ";
  }
  std::cout << std::endl;
}
