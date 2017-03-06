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


#include "GameManager.h"
#include "UIRender.h"
#include "EventHandler.h"
#include "Networker.h"
#include "GameLogic.h"
#include "GameState.h"
#include "StateMachine.h"
#include "UIOptions.h"

UI::GameManager::GameManager(int targetUPS, std::string nickname) {
    // targetUPS is used to control the timing of the main loop //
    this->targetUPS = targetUPS;
    this->nickname = nickname;
    quit = false;
    renderer = Renderer();
    networker = Networker(nickname);
    eventHandler = EventHandler();
    stateMachine = Core::StateMachine();

//    gameLogic = Core::GameLogic();
    initializeSDL();
    renderer.init();

    uiAction.type = Core::NONE;
    uiAction.msg = "";

    networker.init(UI::SIMPLE_CLIENT);
}

void UI::GameManager::mainLoop() {
    Core::GameState gs;
    networker.setNickname(nickname);
    networker.start();
    Options options = renderer.getOptions();
    options.perspective = networker.getTeam();
    renderer.setOptions(options);
    eventHandler.setOptions(options);
    while (!quit) {
        networker.getLastState(gs);
        eventHandler.handleInput();
        if (eventHandler.getLastAction(&uiAction)) {
            std::cout << "Bushes of love? " << uiAction.type << std::endl;
            if (uiAction.type == Core::QUIT) {
                quit = true;
            }
            renderer.setAction(uiAction);
            renderer.handleAction();
        }
        renderer.renderOnce(gs);
        SDL_Delay(25);
    }
    networker.shutdown();
}
/***
std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();

std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() <<std::endl;
std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() <<std::endl;
***/


bool UI::GameManager::initializeSDL() {
// TODO Use SDL_WasInit etc first //
// Modularize Initialization //
    bool success = false;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL::logSDLError(std::cout, "SDL_Init");
        SDL_Quit();
        return success;
    }
    if (SDLNet_Init() == -1) {
        SDL::logSDLNetError(std::cout, "SDLNet_Init");
        SDL_Quit();
        return success;
    }
    success = true;
    return success;
}

void UI::GameManager::setOptions(Options & optionsUi) {
    renderer.setOptions(optionsUi);
    eventHandler.setOptions(optionsUi);
}

