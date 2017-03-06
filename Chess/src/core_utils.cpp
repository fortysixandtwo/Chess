/*****
Copyright (C) 2017 Evangelos Ribeiro Tzaras

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



#include <string>
#include <stdint.h>
#include <iostream>

#include "core_utils.h"


std::string Core::coordinatesToChess(uint8_t posx, uint8_t posy) {
    if (isOnBoard(posx, posy)) {
        char c_str[3];
        c_str[1] = '1' + posy;
        c_str[0] = 'A' + posx;
        c_str[2] = 0;
        std::string coords = c_str;
        return coords;
    }
    return "";
}

bool Core::coordinatesFromChess(const std::string & coords, \
    uint8_t * posx, uint8_t * posy) {
    bool validCoords = false;
    if (coords.size() == 2) {
        *posx = (uint8_t)coords.at(0) - 'A';
        *posy = (uint8_t)coords.at(1) - '1';
        validCoords = isOnBoard(*posx, *posy);
    }
    return validCoords;
}

bool Core::isOnBoard(uint8_t posx, uint8_t posy) {
    if ((posx<8) && (posy<8)) {
        return true;
    }
    return false;
}

bool Core::isMoveStringCorrect(std::string & moveString) {
    bool success = false;
    if (moveString.size() == (4+MOVE_DELIMITER.size())) {
        int index = moveString.find(MOVE_DELIMITER);
        if (index == 2) {
            for (int i=0;i<2;++i) {
                int j = i*(index+MOVE_DELIMITER.size());
                if ((moveString[j+0] >= 'A') && (moveString[j+0] <= 'H') \
                    && (moveString[j+1] >= '0') && (moveString[j+1] <= '9')) {
                    success = true;
                }
            }
        }
    }
    std::cout << "MoveString looking good?" << success << std::endl;
    return success;
}
