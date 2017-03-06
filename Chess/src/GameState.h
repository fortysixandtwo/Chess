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



#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <stdint.h>
#include <string>

namespace Core {

    enum figure_t { ROOK=0, KNIGHT=1, BISHOP=2, QUEEN=3, KING=4, PAWN=5 };
    enum team_t { WHITE=0, BLACK=1, SPECTATOR=3 };

    struct FigureState {
        uint8_t id;
        figure_t figure;
        team_t team;
        uint8_t posx;
        uint8_t posy;
        bool isAlive;
    };

    class GameState {
    public:
        FigureState figures[32];
        GameState(); 
        GameState(const GameState & gs);
        
    //    GameState(std::vector<FigureState> f : figures(f) {};

    };


}

#endif
