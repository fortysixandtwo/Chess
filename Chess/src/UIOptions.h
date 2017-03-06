/*****
This file is part of SDL-Chess.

    SDL-Chess is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SDL-Chess is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SDL-Chess.  If not, see <http://www.gnu.org/licenses/>.

*****/



#ifndef UIOPTIONS_H
#define UIOPTIONS_H

#include <string>
#include "GameState.h"

namespace UI {
    
    class Options {
            
        public:
            int width;
            int height;
            bool fullscreen;
            int tilesize;
            int offset_chessboard_x;
            int offset_chessboard_y;
            std::string theme;
            Core::team_t perspective;

            Options();
            Options(const Options & options);

    };

}


#endif
