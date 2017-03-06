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



#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SDL.h>
#include <string>
#include <vector>

#include "StateMachine.h"
#include "UIOptions.h"

namespace UI {
    class EventHandler {
        private:
            SDL_Event event;
            std::vector<Core::action_t> actions; // Scheduled actions
            // do i really need a vector or can at most one action be performed
            // per update
            Core::action_t action;
            Core::action_t lastAction;
            Core::status_ui_t status;
            Options uiOptions;

            bool clickedOnChessboard( \
                SDL_MouseButtonEvent * event, std::string & tileClicked \
                );
        public:
            EventHandler();
            EventHandler(Options & uiOptions);
            void setOptions(Options & uiOptions);
            bool getLastAction(Core::action_t * action);
            bool handleInput();

    };

}

#endif
