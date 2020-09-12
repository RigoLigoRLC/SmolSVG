#include <iostream>
#include "pathreader.hpp"

int main()
{
  std::string a;

  std::getline(std::cin, a);

  auto path = SmolSVG::readPathString(a);

  for(auto i : *path)
    switch(i->type())
    {
      case SmolSVG::commandType::LineTo:
        std::cout << "Line object" << std::endl;
        break;
      case SmolSVG::commandType::CurveTo:
        std::cout << "Cubic Curve object" << std::endl;
        break;
      case SmolSVG::commandType::QuadTo:
        std::cout << "Quadratic Curve  object" << std::endl;
        break;
      case SmolSVG::commandType::ArcTo:
        std::cout << "Arc object" << std::endl;
        break;
    }

  delete path;
  return 0;
}
