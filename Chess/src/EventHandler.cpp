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



#include <string>
#include <iostream>
#include <SDL.h>

#include "EventHandler.h"
#include "UIOptions.h"
#include "StateMachine.h"
#include "core_utils.h"


UI::EventHandler::EventHandler(Options & uiOptions) {
    // stuff //
    this->uiOptions = uiOptions;
    this->status.type = Core::PREMATCH;
    this->status.chatbuffer = "";
    action.type = Core::NONE;
    action.msg = "";
    lastAction.type = Core::NONE;
    lastAction.msg = "";

}

UI::EventHandler::EventHandler() {
    EventHandler(Options());
}

void UI::EventHandler::setOptions(Options & uiOptions) {
    this->uiOptions = uiOptions;
}

bool UI::EventHandler::getLastAction(Core::action_t * action) {
    bool actionQueued = false;

    if (this->action.type != Core::NONE) {
// i should think of something better, or use another parameter
// to force setting new action even if type==Core::None
//    if (true) {
        action->type = this->action.type;
        action->msg = this->action.msg;
        actionQueued = true;
    }
    // FIXME
    if (this->action.type != Core::NONE) {
        std::cout << "Something is in the bush!" \
            << this->action.type << std::endl;
    }
/***
    if (actions.size()) {
        size_t actionIndex = actions.size()-1;
        action->type = actions.at(i).type;
        action->msg = actions.at(i).msg;
        actionQueued = true;
    }
***/
    return actionQueued;
}

bool UI::EventHandler::handleInput() {
    // returns if any
    bool update = false;
    std::string msg = "";
    while (SDL_PollEvent(&event) && !update) {
        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                if (clickedOnChessboard(&(event.button), msg)) {
                    if (event.button.clicks == 1) {
                        action.type = Core::FIGURE_SELECT;
                    } else {
                        action.type = Core::FIGURE_SHOW_MOVES;
                    }
                    action.msg = msg;

                }
                break;
                
            case SDL_MOUSEBUTTONUP:
                 if (clickedOnChessboard(&(event.button), msg)) {
                    if (lastAction.msg.compare(msg) == 0) {
                        if (event.button.clicks == 1) {
                            action.type = Core::FIGURE_SELECT_RELEASE;
                        } else {
                            action.type = Core::FIGURE_SHOW_MOVES_RELEASE;
                        }
                    } else {
                        action.msg = msg;
                        action.type = Core::FIGURE_MOVE;
                    }
                }
                break;
            case SDL_QUIT:
                // quit //
                action.type = Core::QUIT;
                break;
            default:
                action.type = Core::NONE;
                action.msg = "";
                break;
        }
        if (action.type != Core::NONE) {
            update = true;
            lastAction.type = action.type;
            lastAction.msg = action.msg;
        }
    } 
    if (!update) {
        action.type = Core::NONE;
        action.msg = "";
    }
    return update;
}
    

bool UI::EventHandler::clickedOnChessboard(SDL_MouseButtonEvent * event, \
    std::string & tileClicked) {
    int x = event->x - uiOptions.offset_chessboard_x;
    int x_max = 8*uiOptions.tilesize;
    int y_max = 8*uiOptions.tilesize;
    int y = event->y - uiOptions.offset_chessboard_y;

    bool clickOnBoard = false;
    if ((x>=0) && (x<x_max) && (y>=0) && (y<y_max)) {
        clickOnBoard = true;

    }
    std::cout << "X:" << x << " Y:" << y;
    std::cout << " on Board? " << clickOnBoard << std::endl;

    if (clickOnBoard) {
        uint8_t posx, posy;
        posx = x/uiOptions.tilesize;
        posy = y/uiOptions.tilesize;

        if (uiOptions.perspective != Core::BLACK) {
            posy = 7-posy;
        } else {
            posx = 7-posx;
        }

        std::cout << "x:" << (int)posx << " y:" << (int)posy;
        tileClicked = Core::coordinatesToChess(posx, posy);
        std::cout << " -> " << tileClicked << std::endl;
    }


    return clickOnBoard;
}


