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



#ifndef GameUI_H
#define GameUI_H

#include <SDL.h>
#include "GameLogic.h"
#include "client.h"
#include "server.h"
#include "UIRender.h"
#include "Networker.h"
#include "EventHandler.h"
#include "StateMachine.h"
#include "UIOptions.h"


namespace UI {

    enum ui_state_t {
        INIT, READY, WAITING_ON_SERVER, WAITING_ON_INPUT, WAITING_FOR_PLAYER

    };

    enum ui_action_t {
        FIGURE_SELECTED=1, FIGURE_SHOW_MOVES=2, FIGURE_MOVE=4, \
        TEXT_TYPE=8, TEXT_SEND=16, GAME_FORFEIT=32, GAME_REMATCH=64
    };


    class GameManager {
// The game manager consists mainly of the following 3 Objects //
// which deal with the //
// rendering of the UI, everything network and event Handling on the UI //
// Networking should be done in a separate thread for it not to interfere //
// with the targetUPS/FPS //

        private:
//            ui_state_t state;
            Core::action_t uiAction;
            Renderer renderer;
            Networker networker;
            EventHandler eventHandler;
            Core::StateMachine stateMachine;
            std::string nickname;

// Game specific //
            // Networker decides which gameLogic is to be used for rendering //
            // (Server, Client) run the same logic //
            Core::GameLogic gameLogic;
            bool quit;
            int targetUPS;

        public:
            GameManager(int targetUPS = 30, std::string nickname = "Player");
            void mainLoop();
            bool initializeSDL();
            void setOptions(Options & optionsUi);

    };
}






#endif
