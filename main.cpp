#include <iostream>

#include "argumented-definitions.h"
#include "simple-definitions.h"

int main() {
  check_simple_definitions();

  std::cout << "_________________________________" << std::endl;

  check_argumented_definitions();
  return 0;
}
