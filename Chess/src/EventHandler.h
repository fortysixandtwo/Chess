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
