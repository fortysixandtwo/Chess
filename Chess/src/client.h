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



#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <SDL_net.h>
#include "GameState.h"
#include "GameLogic.h"

namespace Net {
    class Client {
    private:
        UDPsocket udpsock;
        IPaddress serverIP;
        std::string nickname;
        bool connected;
        int id;
        Core::GameLogic gameLogic;
        bool simulateGame;
        bool verbose;
        Core::team_t team;
        int maxRetries;

        void waitForGreet();
    public:
        Client(const std::string & ip, const uint16_t port, \
            const std::string & nickname, bool simulateGame = true,
            bool verbose = false);
        ~Client();

        bool connect(const std::string & password);
        bool disconnect();
        bool sendMsg(std::string & msg);

        std::string getNickname() const;
        void setNickname(std::string & nick);

        bool challengeRematch();
        bool acceptRematch();
//        bool moveFigure(uint8_t id, uint8_t newx, uint8_t newy);
        bool moveFigure(std::string & startCoordinate, std::string & stopCoordinate);
        Core::team_t getTeam() const;
        void getLastState(Core::GameState & gs);
    };

}

#endif
