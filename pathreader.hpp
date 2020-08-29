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

#ifndef SMOLSVG_PATHREADER_H
#define SMOLSVG_PATHREADER_H

#include "svgpath.hpp"
#include <string>

namespace SmolSVG
{
  SVGRawPath readPathString(std::string &pathStr);
}

#endif //INC_0005_SMOLSVG_PATHREADER_H
