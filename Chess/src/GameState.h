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
