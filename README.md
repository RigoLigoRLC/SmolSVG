# SmolSVG
A tiny C++ state machine reads SVG paths and output raw drawing commands.

## Introduction
SmolSVG was a wheel invented firstly specifically for another project of mine -- LC2KiCad. This is a EasyEDA (LCEDA) to KiCad converter in C++. Because I have to deal with all sorts of SVG paths stored inside EasyEDA documents, yet was unable to find a sutiable library to read the SVG paths, I wrote this library, and made it a dedicated project thinking it could be useful for other people as well.

## Use
Drop all `.hpp` files into your project include directory, and include `pathreader.hpp` whereever you need to read SVG paths. Then you just need to do this:
```
auto path = SmolSVG::readPathString(AnySvgPathStdString);
```
SmolSVG will read the path for you. Please notice that a pointer to the path was returned: **the path must be `delete`d manually after use**. This is mostly bacuase C++ will return a copy of the path rather than returning the original object back to the invoker; this will destruct the original object and all the pointers inside will be invalid. I did't bother to use smart pointers there.

The return type of `SmolSVG::readPathString(std::string)` is `SmolSVG::SVGRawPath*`, which consists of following methods:
- `begin()` and `end()` const data iterator;
- `mbegin()` and `mend()` mutable data iterator;
- `addRawCommand(SmolSVG::baseCommand*)` for adding a command at the end of the path;
- `getLastCommand()` for reading back the last command in the path;
- `purgeLastCommand()` for removing the last command from the path **(but not releasing the memory the pointer pointed to!)**
- `purgeDestroyLastCommand()` for first releasing then removing the last command from the path.
These methods allows basic modification to the path. After all we can only read a path, not really going to write it anywhere else, therefore nothing else were provided.

You can fetch each element using range-based `for`:
```
for(auto &i : *path)
  cout << i.type() << endl;
```
Here, the program output the type of each command the path object consists of. But what commands do we have here?

The following commands will be written into the path object by `SmolSVG::readPathString(std::string)`:
- `SmolSVG::commandLineTo` (type(): 3)
- `SmolSVG::commandQuadraticBezierTo` (type(): 8)
- `SmolSVG::commandCurveBezierTo` (type(): 6)
- `SmolSVG::commandEllipticalArcTo` (type(): 10)

Commands like "move to", "close path", "line vertically" and such were processed automatically by the `SmolSVG::readPathString(std::string)` function. By examining the type of each object, you can access the interface of each object with or without a cast.
Every command inherited from `SmolSVG::baseCommand` will have `getConstStartPoint()` and `getConstEndPoint()` member functions. They will return the actual start and end point of the graphic item that this very command draws, for example, the start and end point of a line drawn by 'L' command. Other three command objects will have their own interfaces of getting the command data:
- `SmolSVG::commandCubicBezierTo::getHandleA`, `SmolSVG::commandCubicBezierTo::getHandleB`
- `SmolSVG::commandQuadraticBezierTo::getHandle`
- `SmolSVG::commadnEllipticalArcTo::getFlagSweep`, `SmolSVG::commadnEllipticalArcTo::getLargeArc`, `SmolSVG::commadnEllipticalArcTo::getRadii`, `SmolSVG::commadnEllipticalArcTo::getXAxisRotation`

You can use a switch statement to determine the type of each object, and process them accordingly.
```
for(auto &i : *path)
  switch(i->type()) {
    case SmolSVG::commandType::LineTo:
      //...
      break;
    case SmolSVG::commandType::CubicTo:
      //...
      break;
    case SmolSVG::commandType::QuadTo:
      //...
      break;
    case SmolSVG::commandType::ArcTo:
      //...
      break;
  }
```
At last don't forget deleting the path for the heap's sake.
`delete path;`

## Error handling
SmolSVG isn't made to see errors in paths, nor could it detect its own crash. It's a state machine; if it runs into no state, then it will lock up completely. All the errors it could see is incorrect argument counts. So, only feed SmolSVG with valid SVG paths!

If a valid path locks up the state machine, please report a bug.

## Licensing
Copyright (c) 2020 RigoLigoRLC (or RigoLigo). This program is distributed under MIT license. See LICENSE for detailed information.
