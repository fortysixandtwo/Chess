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


#ifndef COREUTILS_H
#define COREUTILS_H

#include <string>



namespace Core {
    const std::string MOVE_DELIMITER = "->";

    std::string coordinatesToChess(uint8_t posx, uint8_t posy);
    bool coordinatesFromChess( \
        const std::string & coords, uint8_t * posx, uint8_t * posy\
    );
//    bool isOnBoard(const std::string & coords);
    bool isOnBoard(uint8_t posx, uint8_t posy);
    bool isMoveStringCorrect(std::string & moveString);


}


#endif
