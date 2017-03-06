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



#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_net.h>
#include "SDL_utils.h"
#include <iostream>
#include <string>
#include "server.h"
#include "client.h"
#include "GameManager.h"
#include "StateMachine.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
// Tile size: (480 - 32 - 8 ) / 8 //
const int CHESS_TILE_SIZE = 55;



// main program //
int main(int argc, char** argv) {
    /***
    std::cout << Core::FIGURE_SELECT << " " \
        << Core::FIGURE_SELECT_RELEASE << " " \
        << Core::FIGURE_SHOW_MOVES << " " \
        << Core::FIGURE_SHOW_MOVES_RELEASE << " " \
        << std::endl;
    ***/
    std::cout << "Please enter nickname: ";
    std::string nickname;
    std::cin >> nickname;
    bool quit = false;

    /***
    std::string host = "Q";
    uint16_t port = 9999;
    Net::Client client = Net::Client(host, port, nickname);

    std::string password = "sehr_geheim";
    bool connected = client.connect(password);
    if (!connected) {
        std::cout << "Could not establish connection to " << host\
            << " on port " << port << std::endl << "Exiting..." << std::endl;
        quit = true;

    }
    ***/

    if (!quit) {
        UI::GameManager manager = UI::GameManager(30, nickname);
        std::cout << "preLoop" << std::endl;
        manager.mainLoop();

        IMG_Quit();
        SDLNet_Quit();
        SDL_Quit();
        return 0;
    } else {
        return 1;
    }

}

