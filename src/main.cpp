#include <iostream>
#include <string>

int main(int, char**) {
  std::string a;

  while (std::cin >> a)
    std::cout << a << '\n';
}
