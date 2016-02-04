#include <iostream>

constexpr auto hello_scream = u8R"delimeter(

                THIS STRING WAS A COMPILE TIME CONSTANT 😱

)delimeter";

int main() {
  std::cout << hello_scream;
  return 0;
}

