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



#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <SDL_net.h>
#include <vector>
#include "net_utils.h"
#include "GameState.h"
#include "GameLogic.h"

// SDL_net should be easier than dealing with Unix Sockets + Winsock //

// Server Status //
// WAITING while waiting for clients //
// STALLED if one client loses connection //

namespace Net {
    enum status_t { WAITING, PRE_MATCH, MATCH, POST_MATCH, STALLED };


    class Server {
    private:
        UDPsocket udpsock;
        uint16_t port;
        IPaddress serverIP;
        std::vector<IPaddress> clientCandidates;
        std::vector<client_t> clients;
        std::string password;
        status_t serverStatus;
        Core::GameLogic gameLogic;
        bool isListening;
        bool simulateGame; // off in case of a proxy for spectators :D //
        bool verbose;

        bool newClientId(uint8_t * id);
        bool handleRequest(request_t request, IPaddress * address, std::string & msg);
        bool handshake(IPaddress * address, std::string & msg);
        bool acceptClient(IPaddress * address, std::string & msg);
        bool acceptDisconnect(IPaddress * address, std::string & msg);
        int getClientIndex(IPaddress * address);
        Core::team_t getTeam();
        void clientGreeting();
        bool tryMove(IPaddress * address, std::string & msg);
        void chat(IPaddress * address, std::string & msg);
        bool challengeRematch(IPaddress * address, std::string & msg);
        bool isNicknameUnique(const std::string & nick);
        void disconnectClient(IPaddress * address, std::string & msg);
    public:
        Server(uint16_t portno, const std::string & password, \
            bool simulateGame = true, bool verbose = false);
        Server();
        ~Server();

        bool listenForRequest();
        void getLastState(Core::GameState & gs);

        IPaddress getIPAddress() const;
        void broadcastMsgToClients(std::string & msg);
        void startNewGame();
        bool startServer();
        void waitForClients();
        void disconnectClient(client_t client);
        status_t status();
        void shutdown();
    };

}


#endif
