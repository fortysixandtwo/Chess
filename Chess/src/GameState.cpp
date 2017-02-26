#include "GameState.h"


Core::GameState::GameState() {
    // initialize new game //

    for (uint8_t i=0;i<32;++i) {
        figures[i].id = i;
        figures[i].isAlive = true;

    // Set position and team and figure type //

        switch ( i % 8 ) {
            case 0:
                figures[i].figure = ROOK;
                break;
            case 1:
                figures[i].figure = KNIGHT;
                break;
            case 2:
                figures[i].figure = BISHOP;
                break;
            case 3:
                figures[i].figure = QUEEN;
                break;
            case 4:
                figures[i].figure = KING;
                break;
            case 5:
                figures[i].figure = BISHOP;
                break;
            case 6:
                figures[i].figure = KNIGHT;
                break;
            case 7:
                figures[i].figure = ROOK;
                break;
            default:
                break;
        }

        figures[i].posx = i % 8;
        if (i/16 == 0) {
            figures[i].team = WHITE;
            if (i/8 == 0) {
                figures[i].posy = 0;
            } else {
                figures[i].posy = 1;
                figures[i].figure = PAWN;
            }
        } else {
            figures[i].team = BLACK;
            if (i/8 == 2) {
                figures[i].posy = 6;
                figures[i].figure = PAWN;
            } else {
                figures[i].posy = 7;
            }
        }

    }
    // end of figure setup //
}

Core::GameState::GameState(const GameState & gs) {
    for (uint8_t i=0;i<32;++i) {
        figures[i].id = gs.figures[i].id;
        figures[i].figure = gs.figures[i].figure;
        figures[i].team = gs.figures[i].team;
        figures[i].posx = gs.figures[i].posx;
        figures[i].posy = gs.figures[i].posy;
        figures[i].isAlive = gs.figures[i].isAlive;
    }
}

        

