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



#include <iostream>
#include <string>
#include <SDL_net.h>
#include <SDL.h>

#include "client.h"
#include "SDL_utils.h"
#include "net_utils.h"
#include "core_utils.h"
#include "version.h"
#include "GameState.h"



#define DELAY 200

Net::Client::Client(const std::string & ip, const uint16_t port, \
    const std::string & nickname, bool simulateGame, bool verbose) {
    // Client for chess matches //
    this->nickname = nickname;
    this->simulateGame = simulateGame;
    this->verbose = verbose;
    connected = false;
    id = 0;
    team = Core::WHITE;
    maxRetries = 5;
    udpsock = SDLNet_UDP_Open(0);
    if (!udpsock) {
        SDL::logSDLNetError(std::cout, "SDLNet_UDP_Open()");
    }
    // Convert port to network byte order //
    uint16_t portn;
    SDLNet_Write16(port, &portn);
    if (SDLNet_ResolveHost(&serverIP, ip.c_str(), portn) != 0) {
        SDL::logSDLNetError(std::cout, "SDLNet_ResolveHost");
    }
    gameLogic = Core::GameLogic();

}

void Net::Client::getLastState(Core::GameState & gs) {
    if (simulateGame) {
        gameLogic.getLastState(gs);
    }
}
    

Net::Client::~Client() {
    SDLNet_UDP_Close(udpsock);
}

Core::team_t Net::Client::getTeam() const {
    return team;
}

bool Net::Client::connect(const std::string & password) {

    std::cout << "Connection to " << Net::resolveAddress(&serverIP);

    int retries = 0;
    bool success = false;
    request_t request;
    std::string outMsg = getVersionString();
    std::string inMsg = "";
// Send handshake and wait for a response //
    success = Net::sendAndReceive(udpsock, &serverIP, HELLO, outMsg, \
        &request, &inMsg, DELAY, verbose);

    if (!success) {
        std::cout << " failed." << std::endl;
        std::cout << " STAGE 1" << std::endl;
    } else {
        if (request == INVALID) {
            success = false;
            std::cout << " failed due to a version missmatch" << std::endl;
            std::cout << "Client: " << getVersionString() \
                << " Server: " << inMsg << std::endl;
        } else {
            // TODO password should also be used here //
            outMsg = nickname;
            success = Net::sendAndReceive(udpsock, &serverIP, CONNECT, outMsg, \
                &request, &inMsg, DELAY, verbose);
            if (!success) {
                if (request == INVALID) {
                    std::cout << " failed:" << std::endl;
                    std::cout << inMsg << std::endl;
                }
            } else {
                if (request == VALID) {
                    int indexDelimiter = inMsg.find(MSG_DELIMITER);
                    std::string clientId = inMsg.substr(0, indexDelimiter);
                    id = stoi(clientId);
                    std::string teamId = inMsg.substr(indexDelimiter+1);
                    team = (Core::team_t)stoi(teamId);
                }
            }
        }
    }
    if (success) {
        std::cout << " succeeded." << std::endl;
// TODO set client id by server msg //
        connected = true;
        SDL_Delay(30);
        waitForGreet();
    }

    return success;
}

void Net::Client::waitForGreet() {
    request_t request;
    std::string inMsg;
    for (int i=0;i<maxRetries;++i) {
        if (Net::recv(udpsock, &serverIP, &request, &inMsg)) {
            if (request == GREET) {
                std::cout << "Received greeting: " << inMsg << std::endl;
                break;
            } else {
                std::cout << "No Greeting: " << request << " " << inMsg << std::endl;
            }
        }
        SDL_Delay(DELAY);
    }
}



bool Net::Client::disconnect() {
    bool success = false;
    if (connected) {
        std::string outMsg = "";
        request_t request;
        std::string inMsg = ""; 
        success = Net::sendAndReceive(udpsock, &serverIP, DISCONNECT, outMsg, \
            &request, &inMsg, DELAY, verbose);
        std::cout << "Disconnect: " << success << "  " << outMsg << std::endl;
        if (success) {
            if (request != VALID) {
                success = false;
            }
        }
    }
    return success;
}

std::string Net::Client::getNickname() const {
    return nickname;
}

void Net::Client::setNickname(std::string & nickname) {
    this->nickname = nickname;
}

bool Net::Client::moveFigure(std::string & startCoordinate, \
    std::string & stopCoordinate) {
    uint8_t posx, posy;
    int fig_id;
    bool success = Core::coordinatesFromChess(startCoordinate, &posx, &posy);
    if (success) {
        fig_id = gameLogic.getFigureOnTile(posx, posy);
        if ((fig_id >= 0) && (fig_id < 32)) {
            success = Core::coordinatesFromChess(stopCoordinate,
                &posx, &posy);
        }
    }
    if (success) {
        if (simulateGame) {
            success = gameLogic.validateMove(fig_id, posx, posy);
        }
        if (success) {
            gameLogic.moveFigure(fig_id, posx, posy);
            request_t request;
            std::string inMsg = "";
            std::string outMsg = startCoordinate + Core::MOVE_DELIMITER + stopCoordinate;
            // FIXME something is going on here ! //
            success = Net::sendAndReceive(udpsock, &serverIP, MOVE, outMsg, \
                &request, &inMsg, DELAY, verbose);
            std::cout << "in[" << request << "]: " << inMsg << std::endl;
        }
    }
    return success;
}


/**
bool Net::Client::moveFigure(uint8_t id, uint8_t newx, uint8_t newy) {
    bool success = false;
    if (simulateGame) {
        success = gameLogic.moveFigure(id, newx, newy);
        if (success) {
            // network dat shiat
        }
    }
    return success;
}
**/
