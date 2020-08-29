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

#ifndef SMOLSVG_SVGPATH_HPP
#define SMOLSVG_SVGPATH_HPP

#include "svgcommands.hpp"

namespace SmolSVG
{
  class SVGRawPath
  {
      std::vector<baseCommand*> commandStorage;
    public:
      std::vector<baseCommand*>::iterator begin() { return commandStorage.begin(); }
      std::vector<baseCommand*>::iterator end() { return commandStorage.end(); }
      void addRawCommand(baseCommand* cmd) { commandStorage.emplace_back(cmd); }
      baseCommand* getLastCommand() { return commandStorage.back(); };
      void purgeLastCommand() { commandStorage.pop_back(); }
      void purgeDestroyLastCommand()
      {
        if(commandStorage.size())
          delete *(commandStorage.end() - 1), purgeLastCommand();
      }
      SVGRawPath()
      {
        commandStorage.clear();
      }
      ~SVGRawPath()
      {
        for (auto &i : commandStorage)
          if (i)
            delete i, i = nullptr;
      }
  };
}

#endif //INC_0005_SMOLSVG_SVGPATH_H
