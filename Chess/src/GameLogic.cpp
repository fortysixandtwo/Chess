#include "GameLogic.h"
#include "GameState.h"
#include <iostream>

Core::GameLogic::GameLogic(bool simulateGame) {
    this->simulateGame = simulateGame;
    Core::GameLogic::restartGame();
}

void Core::GameLogic::restartGame() {
    wasLastStateFetched = false;
    Core::GameState gs = Core::GameState();
    states.clear();
    states.push_back(gs);
}

int Core::GameLogic::getFigureOnTile(uint8_t posx, uint8_t posy) const {
    const GameState * gs = &(states.at(states.size()-1));
    for (uint8_t i=0;i<32;++i) {
        if ((gs->figures[i].posx == posx) && (gs->figures[i].posy == posy)) {
            return gs->figures[i].id;
        }
    }
    return -1;
}

bool Core::GameLogic::validateMove(uint8_t fig_id, uint8_t posx, uint8_t posy) const {
    bool isValid = true;

    int target_id = getFigureOnTile(posx, posy);
    const GameState * gs = &(states.at(states.size()-1));

    // Check if new position is on the board //
    if ((posx>7) || (posy>7)) {
        isValid = false;
    }
    
    // Check if it is the selected figures turn //
    if (getActivePlayer() != gs->figures[fig_id].team) {
        isValid = false;
    }
    // Dead figures cant move //
    if (!gs->figures[fig_id].isAlive) {
        isValid = false;
    }

    // Check if new position is occupied //
    if (target_id != -1) {
        if (gs->figures[fig_id].team == gs->figures[target_id].team) {
            isValid = false;
        }
        
    } 

    // TODO //
    // Actually checking whether the selected figure can move there //



    return isValid;
}

bool Core::GameLogic::moveFigure(uint8_t fig_id, uint8_t posx, uint8_t posy) {
    bool moveValid = true;
    if (simulateGame) {
        moveValid = Core::GameLogic::validateMove(fig_id, posx, posy);
    }
    if (moveValid) {
        GameState newState = GameState(states.at(states.size()-1));
        int target_id = Core::GameLogic::getFigureOnTile(posx, posy);

    // Check if new position is occupied and kill it if it is //
        if (target_id != -1) {
            newState.figures[target_id].isAlive = false;
        }
        newState.figures[fig_id].posx = posx;
        newState.figures[fig_id].posy = posy;
        states.push_back(newState);
        wasLastStateFetched = false;
    }
    return moveValid;
}

Core::team_t Core::GameLogic::getActivePlayer() const {
    Core::team_t activePlayer;
    if (states.size() % 2 == 0) {
        activePlayer = BLACK;
    } else {
        activePlayer = WHITE;
    }
    return activePlayer;
}
    
bool Core::GameLogic::getLastState(GameState & gs) {
    // Returns true if there is a new state //
    if (!wasLastStateFetched) {
        gs = GameState(states.at(states.size()-1));
        wasLastStateFetched = true;
        return wasLastStateFetched;
    }
    return wasLastStateFetched;
}
