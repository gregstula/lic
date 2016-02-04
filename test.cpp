#include <iostream>

constexpr auto hello_scream = u8R"delimeter(

                HELLO 😱

)delimeter";

int main() {
  std::cout << hello_scream;
  return 0;
}

