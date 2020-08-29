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
#ifndef SMOLSVG_SVGCOMMANDS_HPP_
#define SMOLSVG_SVGCOMMANDS_HPP_

#include <vector>

namespace SmolSVG
{
  struct SmolCoord
  {
    double X, Y;
    SmolCoord operator+(const SmolCoord &o) { return { this->X + o.X, this->Y + o.Y }; }
    SmolCoord operator-(const SmolCoord &o) { return { this->X - o.X, this->Y - o.Y }; }
    SmolCoord operator*(const double &o) { return { this->X * o, this->Y * o }; }
    SmolCoord(const double x, const double y) { X = x, Y = y; }
    SmolCoord() { X = Y = 0.0; }
  };

  class baseCommand
  {
      virtual std::vector<SmolCoord> linearize() = 0;

    public:
      baseCommand() { relative = false; }
      virtual ~baseCommand() = default;
      const SmolCoord& getConstStartPoint() { return pointFrom; }
      const SmolCoord& getConstEndPoint() { return pointTo; }

    protected:
      SmolCoord pointFrom, pointTo;
      bool relative;
  };

  class commandLineTo : public baseCommand
  {
    public:
      commandLineTo(const double pFromX, const double pFromY, const double pToX, const double pToY)
        { pointFrom.X = pFromX, pointFrom.Y = pFromY, pointTo.X = pToX, pointTo.Y = pToY; }
      commandLineTo(const SmolCoord &pFrom,  const SmolCoord &pTo) { pointFrom = pFrom, pointTo = pTo; }

      std::vector<SmolCoord> linearize();
  };

  class commandQuadraticBezierTo : public baseCommand
  {
      SmolCoord pointHandle;
    public:
      commandQuadraticBezierTo(const double pFromX, const double pFromY, const double pHandleX, const double pHandleY,
                               const double pToX, const double pToY)
      {
        pointFrom.X = pFromX, pointFrom.Y = pFromY, pointHandle.X = pHandleX, pointHandle.Y = pHandleY,
        pointTo.X = pToX, pointTo.Y = pToY;
      }
      commandQuadraticBezierTo(const SmolCoord &pFrom, const SmolCoord &pHandle, const SmolCoord &pTo)
        { pointFrom = pFrom, pointHandle = pHandle, pointTo = pTo; }

      std::vector<SmolCoord> linearize();
  };

  class commandCubicBezierTo : public baseCommand
  {
      SmolCoord pointHandleA, pointHandleB;
    public:
      commandCubicBezierTo(const double pFromX, const double pFromY, const double pHandleAX, const double pHandleAY,
                           const double pHandleBX, const double pHandleBY, const double pToX, const double pToY)
      {
        pointFrom.X = pFromX, pointFrom.Y = pFromY, pointHandleA.X = pHandleAX, pointHandleA.Y = pHandleAY,
        pointHandleB.X = pHandleBX, pointHandleB.Y = pHandleBY, pointTo.X = pToX, pointTo.Y = pToY;
      }
      commandCubicBezierTo(const SmolCoord &pFrom, const SmolCoord &pHandleA, const SmolCoord &pHandleB,
                           const SmolCoord &pTo)
      { pointFrom = pFrom, pointHandleA = pHandleA, pointHandleB = pHandleB, pointTo = pTo; }

      std::vector<SmolCoord> linearize();
  };

  class commandEllipticalArcTo : public baseCommand
  {
      SmolCoord radii;
      double XAxisRotation;
      bool flagLargeArc, flagSweep;
    public:
      commandEllipticalArcTo(const double pFromX, const double pFromY, const double pRadiiX, const double pRadiiY,
                             const double XAxisRot, const bool largeArc, const bool sweep, const double pToX,
                             const double pToY)
      {
        pointFrom.X = pFromX, pointFrom.Y = pFromY, radii.X = pRadiiX, radii.Y = pRadiiY, XAxisRotation = XAxisRot,
        flagLargeArc = largeArc, flagSweep = sweep, pointTo.X = pToX, pointTo.Y = pToY;
      }
      commandEllipticalArcTo(const SmolCoord &pFrom, const SmolCoord pRadii, const double XAxisRot, const bool largeArc,
                             const bool sweep, const SmolCoord pTo)
      {
        pointFrom = pFrom, radii = pRadii, XAxisRotation = XAxisRot, flagLargeArc = largeArc, flagSweep = sweep,
        pointTo = pTo;
      }

      std::vector<SmolCoord> linearize();
  };
}

#endif