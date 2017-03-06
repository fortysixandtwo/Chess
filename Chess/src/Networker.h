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



#ifndef NETWORKER_H
#define NETWORKER_H

#include <vector>

#include <SDL_net.h>
#include "net_utils.h"
#include "server.h"
#include "client.h"
#include "net_utils.h"
#include "StateMachine.h"


namespace UI {

    enum networking_t {
        SIMPLE_CLIENT, FULL_CLIENT, FULL_CLIENT_LOCAL
    };

    enum task_status_t {
        SEND, SEND_DONE, WAIT_FOR_CONFIRMATION, RECEIVE, RECEIVE_DONE, \
        COMPLETED
    };

    struct task_t {
        Net::request_t request;
        task_status_t status;
    };

    class Networker {
        private:
            bool isServerDedicated;
//            ui_state_t uiState;
            Core::action_t uiAction;
            networking_t type;
            bool isInitialized;
            bool isRunning;
            std::string nickname;
            Net::Server * server;
            std::string ip;
            uint16_t port;
            std::string password;
            std::vector<Net::Client *> clients;
// everything that needs to be networked to or from the server //
// GameManager should set outTasks and get/perform inTasks //
            std::vector<task_t> outTasks; 
            std::vector<task_t> inTasks;


            void addClient(Net::Client & client);
            void startServer(Net::Server & server);


        public:
            Networker(std::string nickname = "Player");
            Core::team_t getTeam() const;
            bool setNickname(std::string nickname, int id = 0);
            bool setNetworkingType(const networking_t & networkingType);
            bool addClient(const std::string & nickname);
            bool init(networking_t networkingType);
            bool start();
            void shutdown();
            void reset();
            void getLastState(Core::GameState & state);
            // QUEUEUEUEUEUE
            void addTask(task_t task);
            void handleTasks();

    };

}
            


#endif
