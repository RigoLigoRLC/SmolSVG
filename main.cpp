#include <iostream>
#include "pathreader.hpp"

int main()
{
  std::string a;

  std::getline(std::cin, a);

  SmolSVG::readPathString(a);
  std::cout << "Hello, World!" << std::endl;
  return 0;
}
