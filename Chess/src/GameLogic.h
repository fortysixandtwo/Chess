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



#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "GameState.h"
#include <string>
#include <vector>
//#include "timeRule.h"

namespace Core {
    class GameLogic {
    private:
        std::vector<GameState> states;
//        TimeRule timeRule;
        bool wasLastStateFetched;
        bool simulateGame;

    public:
        GameLogic(bool simulateGame = true);

        bool validateMove(uint8_t fig_id, uint8_t newx, uint8_t newy) const;
        bool moveFigure(uint8_t fig_id, uint8_t newx, uint8_t newy);
        int getFigureOnTile(uint8_t posx, uint8_t posy) const;
        void restartGame();
        team_t getActivePlayer() const;
        void saveGameDataToFile(std::string & filepath) const;
        void loadGameDataFromFile(std::string & filepath);
        bool getLastState(GameState & gs);
    };
}

#endif
