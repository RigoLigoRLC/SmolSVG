/*
    Copyright (c) 2020 RigoLigoRLC.

    This file is part of SmolSVG.

    SmolSVG is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version.

    SmolSVG is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with SmolSVG. If not, see <https://www.gnu.org/licenses/>.
*/

#include "svgcommands.hpp"

namespace SmolSVG
{
  std::vector<SmolCoord> commandLineTo::linearize()
  {
    std::vector<SmolCoord> ret { pointFrom, pointTo };
    return ret;
  }

  std::vector<SmolCoord> commandQuadraticBezierTo::linearize()
  {
    std::vector<SmolCoord> ret; // TODO stub quadratic bezier

    return ret;
  }

  std::vector<SmolCoord> commandCubicBezierTo::linearize()
  {
    std::vector<SmolCoord> ret; // TODO stub cubic bezier
    return ret;
  }

  std::vector<SmolCoord> commandEllipticalArcTo::linearize()
  {
    std::vector<SmolCoord> ret; // TODO stub elliptical arc
    return ret;
  }
}