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
