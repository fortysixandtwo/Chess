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

#include <SDL.h>
#include <SDL_net.h>

#include "server.h"
#include "SDL_utils.h"
#include "net_utils.h"
#include "version.h"
#include "GameLogic.h"
#include "core_utils.h"

#define TIMEOUT 45
#define DELAY 50
#define PORT 9999

Net::Server::Server(const uint16_t port, const std::string & password, \
    bool simulateGame, bool verbose) {
// Server for chess match //
// validates gamestates and networks between clients //
    this->port = port;
    this->password = password;
    this->isListening = false;
    this->verbose = verbose;
    this->simulateGame = simulateGame;
    gameLogic = Core::GameLogic(simulateGame);

    }

Net::Server::Server() {
    Server(0, "sehr_geheim", true, false);
}


Net::Server::~Server() {
    shutdown();
}

bool Net::Server::startServer() {
    bool success = true;

    if (isListening) {
        success = false;
    } else {
        uint16_t portn;
        SDLNet_Write16(port, &portn);
        udpsock = SDLNet_UDP_Open(portn);
        if (!udpsock) {
            SDL::logSDLNetError(std::cout, "SDLNet_UDP_Open()");
            success = false;
        } else {
            std::cout << "Starting ChesServ v" << getVersionString() << std::endl;
            std::cout << "Listening at port " << port << std::endl;
            isListening = true;
            success = true;
        }
    }
    return success;
}


void Net::Server::shutdown() {
    if (isListening) {
        SDLNet_UDP_Close(udpsock);
        isListening = false;
    }
}

void Net::Server::getLastState(Core::GameState & gs) {
    if (simulateGame) {
        gameLogic.getLastState(gs);
    }
}


void Net::Server::broadcastMsgToClients(std::string & msg) {
    for (uint8_t i=0;i<clients.size();++i) {
        Net::send(udpsock, &(clients.at(i).address), SERVERMSG, msg);
    }
}

bool Net::Server::isNicknameUnique(const std::string & nick) {
    // nick should be stripped of whitespaces etc //
    bool nicknameUnique = true;
    for (size_t i=0;i<clients.size();++i) {
        if (nick.compare(clients.at(i).nickname) == 0) {
            nicknameUnique = false;
            break;
        }
    }
    return nicknameUnique;
}

IPaddress Net::Server::getIPAddress() const {
    return serverIP;
}

bool Net::Server::listenForRequest() {
    // new //
    bool success = false;
    IPaddress address;
    request_t request;
    std::string msg;

    success = Net::recv(udpsock, &address, &request, &msg);
    if (success) {
        success = handleRequest(request, &address, msg);
    }
    return success;
}


bool Net::Server::handleRequest(request_t request, IPaddress * address, \
    std::string & msg) {
    switch (request) {
        case HELLO:
            handshake(address, msg); 
            break;
        case CONNECT:
            acceptClient(address, msg);
            break;
        case DISCONNECT:
            acceptDisconnect(address, msg);
            break;
        case MOVE:
            tryMove(address, msg);
            break;
        case CHAT:
            chat(address, msg);
            break;
        case REMATCH:
            challengeRematch(address, msg);
            break;
        default:
            break;
    }
    return true;
}


bool Net::Server::acceptClient(IPaddress * address, std::string & msg) {

    bool validClient = false;
    // Check if the client succeeded the handshake //
    for (uint8_t i=0;i<clientCandidates.size();++i) {
        if ((address->host == clientCandidates.at(i).host) && \
            (address->port == clientCandidates.at(i).port)) {
            validClient = true;
        }
    }
    if (validClient) {
            if (isNicknameUnique(msg)) {
// Assign the new Client //
            client_t newClient;
            newClient.id = clients.size();
            newClient.nickname = msg;
            newClient.address = *address;
// First player is white, second player black
// every other spectator
/**
            switch (clients.size()) {
                case 0:
                    newClient.team = Core::WHITE;
                    break;
                case 1:
                    newClient.team = Core::BLACK;
                    break;
                default:
                    newClient.team = Core::SPECTATOR;
            }
            **/
            newClient.team = getTeam();
            std::cout << "Client [" << (int)newClient.id << "] " \
                << newClient.nickname;
            if (verbose) {
                std::cout << " (" << Net::resolveAddress(address) << ") joined "; 
            } else {
                std::cout << " joined ";
            }
            if (newClient.team == Core::WHITE) {
                std::cout << "team white." << std::endl;
            } else if (newClient.team == Core::BLACK) {
                std::cout << "team black." << std::endl;
            } else {
                std::cout << "spectators." << std::endl;
            }
            // Inform the client of the success //
            std::string outMsg = std::to_string(newClient.id) + \
                MSG_DELIMITER + std::to_string(newClient.team);
            Net::send(udpsock, address, VALID, outMsg);
            clients.push_back(newClient);
            SDL_Delay(50);
            clientGreeting();
        } else {
            std::string outMsg = "Nickname in use. Please retry!";
            Net::send(udpsock, address, INVALID, outMsg);
            validClient = false;
        }
    }
    return validClient;
}

Core::team_t Net::Server::getTeam() {
    bool gotWhitePlayer = false;
    bool gotBlackPlayer = false;
    for (size_t i=0;i<clients.size();++i) {
        if (clients.at(i).team == Core::WHITE) {
            gotWhitePlayer = true;
        } else if (clients.at(i).team == Core::BLACK) {
            gotBlackPlayer = true;
        }
    }
    if (!gotWhitePlayer) {
        return Core::WHITE;
    }
    if (!gotBlackPlayer) {
        return Core::BLACK;
    }
    return Core::SPECTATOR;
}

void Net::Server::clientGreeting() {
    // Make clients known to each other //
    // and share nickname, team (ELO?) //
    // maybe we could just assume that the last entry in clients //
    // is the newest player we are trying to introduce to the rest //
    std::string messageToNewPlayer = "";
    uint8_t newPlayerIndex = clients.size()-1;
    std::string messageToOldPlayers = clients.at(newPlayerIndex).nickname;
    switch (clients.at(newPlayerIndex).team) {
        case Core::WHITE:
            messageToOldPlayers = messageToOldPlayers + " W ";
            break;
        case Core::BLACK:
            messageToOldPlayers = messageToOldPlayers + " B ";
            break;
        case Core::SPECTATOR:
            messageToOldPlayers = messageToOldPlayers + " S ";
            break;
    }
    for (uint8_t i=0;i<clients.size()-1;++i) {
        messageToNewPlayer = messageToNewPlayer + clients.at(i).nickname;
        switch (clients.at(i).team) {
            case Core::WHITE:
                messageToNewPlayer = messageToNewPlayer + " W ";
                break;
            case Core::BLACK:
                messageToNewPlayer = messageToNewPlayer + " B ";
                break;
            case Core::SPECTATOR:
                messageToNewPlayer = messageToNewPlayer + " S ";
                break;
        }
        Net::send(udpsock, &(clients.at(i).address), GREET, messageToOldPlayers);
    }
    Net::send(udpsock, &(clients.at(newPlayerIndex).address), GREET, messageToNewPlayer);
}


bool Net::Server::handshake(IPaddress * address, std::string & msg) {
    // //
    bool success = false;
    std::cout << "Incoming handshake from ";
    std::cout << Net::resolveAddress(address) << " " << msg << std::endl;

    bool versionMatch = false;
    std::string serverVersion = getVersionString();
    
    if (serverVersion.compare(msg) == 0) {
        versionMatch = true;
    }
    if (versionMatch) {
        success = Net::send(udpsock, address, VALID, serverVersion);
    } else {
        Net::send(udpsock, address, INVALID, serverVersion);
    }

    if (success) {
        clientCandidates.push_back(*address);
    }

    return success;
}

bool Net::Server::tryMove(IPaddress * address, std::string & msg) {
    bool success = true;
    std::cout << "::Incoming move" << msg << std::endl;
    int fig_id;
    uint8_t posx, posy;
    success = Core::isMoveStringCorrect(msg);
    std::string start,stop;
    int index = msg.find(Core::MOVE_DELIMITER.c_str(), 0, MSG_DELIMITER.size());
    if (success) {
        start = msg.substr(0, index);
        success = Core::coordinatesFromChess(start, &posx, &posy);
    }
    if (success) {
        fig_id = gameLogic.getFigureOnTile(posx, posy);
        if (fig_id == -1) {
            success = false;
        }
    }
    if (success) {
        stop = msg.substr(index+Core::MOVE_DELIMITER.size());
        success = Core::coordinatesFromChess(stop, &posx, &posy);
        success = gameLogic.moveFigure(fig_id, posx, posy);
        std::cout << "gameLogic.moveFigure(): " << success << std::endl;
    }
    if (success) {
        std::cout << "Move seems reasonable. Networking...." << std::endl;
        success = Net::send(udpsock, address, VALID, msg);
    }

    return success;
}


void Net::Server::chat(IPaddress * address, std::string & msg) {

}
 

bool Net::Server::challengeRematch(IPaddress * address, std::string & msg) {
    bool success = true;

    return success;
}


void Net::Server::disconnectClient(IPaddress * address, std::string & msg) {


}

bool Net::Server::acceptDisconnect(IPaddress * address, std::string & msg) {
    int clientIndex = getClientIndex(address);
    bool success = false;
    if (clientIndex >= 0) {
        std::string outMsg = "Confirmed disconnect: " + msg;
        success = Net::send(udpsock, address, VALID, outMsg);
        std::cout << "Confirming disconnect of client " \
            << clients.at(clientIndex).nickname;
        clients.erase(clients.begin()+clientIndex);
        if (success) {
            std::cout << " succeeded." << std::endl;
        } else {
            std::cout << " failed." << std::endl;
        }
    } else {
        std::cout << "Unknown client (" << Net::resolveAddress(address) \
            << ") tried disconnecting..." << std::endl;
        msg = "You are not a valid client!";
        Net::send(udpsock, address, INVALID, msg);
    }
    return success;
}

int Net::Server::getClientIndex(IPaddress * address) {
    int index = -1;
    for (size_t i=0;i<clients.size();++i) {
        if ((clients.at(i).address.host == address->host) \
            && (clients.at(i).address.port == address->port)) {
            index = i;
            break;
        }
    }
    return index;
}


void Net::Server::waitForClients() {
    //
    /****
    UDPpacket * packet;
    packet = SDLNet_AllocPacket(512);
    int numrecv;
    
    while (clients.size()<2) {
    // Wait for 2 players before continuing //
        numrecv = SDLNet_UDP_Recv(udpsock, packet);
        if (numrecv>0) {
            std::cout << "numrecv " << numrecv << std::endl;
    // perform handshake and register client //
            if (packet->data[0] == HELLO) {
    // check if client is already in client list //
                bool isNewClient = true;
                for (uint8_t i=0;i<clients.size();++i) {
                    if ((clients.at(i).host == packet->address.host) && \
                        (clients.at(i).port == packet->address.port)) {
                        std::cout << "Known client tried to handshake!" << std::endl;
                        std::cout << "IP: " << packet->address.host << ":";
                        std::cout << packet->address.port << std::endl;
                        isNewClient = false;
                    } 
                }

                if (isNewClient) {
                    clients.push_back(packet->address);
                }
            }
        } else if (numrecv == -1) {
            SDL::logSDLNetError(std::cout, "SDLNet_UDP_Recv");
        }
    SDL_Delay(75);
    }
    SDLNet_FreePacket(packet);
    ****/

}
