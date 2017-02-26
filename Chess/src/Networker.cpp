#include "Networker.h"

#include "net_utils.h"

#include <vector>
#include <iostream>
#include <string>
#include "server.h"
#include "client.h"
#include "GameState.h"

UI::Networker::Networker(std::string nickname) {
    isServerDedicated = true;
    server = NULL;
    type = SIMPLE_CLIENT;
    isInitialized = false;
    isRunning = false;
    ip = "Q";
    port = 9999;
    password = "sehr_geheim";
    this->nickname = nickname;
}

bool UI::Networker::setNickname(std::string nickname, int id) {
    bool success = false;;
    switch (id) {
        case 0:
        case 1:
            if (clients.size() > id) {
                clients.at(id)->setNickname(nickname);
                success = true;
            }  
            break;
        default:
            success = false;
    }
    return success;
}

Core::team_t UI::Networker::getTeam() const {
    return clients.at(0)->getTeam();
}

bool UI::Networker::setNetworkingType(const networking_t & networkingType) {
    if (!isRunning) {
        type = networkingType;
        return true;
    } else {
        return false;
    }
}

bool UI::Networker::init(networking_t networkingType) {
    if (isRunning) {
// shutdown cleanly and reinit //
        shutdown();
    } 
    Net::Client * player1 = NULL;
    Net::Client * player2 = NULL;
    switch (networkingType) {
        case FULL_CLIENT_LOCAL:
            player2 = new Net::Client(
                ip, port, "Player 2", false, true);
        case FULL_CLIENT:
            server = new Net::Server(
                port, password, true, true);
        case SIMPLE_CLIENT:
            player1 = new Net::Client(
                ip, port, "Player 1", true, true);
            clients.push_back(player1);
    }
    type = networkingType;
// handle second player here because of switch statement falltrough //
    if (type == FULL_CLIENT_LOCAL) {
        clients.push_back(player2);
    }
// perform sanity check on clients and server to verify and set  //
// isRunning accordingly //
    isInitialized = true;
    return isInitialized;
}

void UI::Networker::shutdown() {
// shut everything down and free memory //
    isRunning = false;
    switch (type) {
        case FULL_CLIENT_LOCAL:
            clients.at(1)->disconnect();
        case FULL_CLIENT:
            server->shutdown();
        case SIMPLE_CLIENT:
            clients.at(0)->disconnect();
    }
// Clean up server //
    if (server) {
        delete server;
        server = NULL;
    }
// Clean up clients //
    for (size_t i=0;i<clients.size();++i) {
        if (clients.at(i)) {
            delete clients.at(i);
        }
    }
}

void UI::Networker::reset() {
    init(type);
    start();
}

bool UI::Networker::start() {
// Make sure clients are connected //
    if (isInitialized) {
        switch (type) {
            //
            case FULL_CLIENT_LOCAL:
            case FULL_CLIENT:
                server->startServer();
            case SIMPLE_CLIENT:
                clients.at(0)->connect(password);
        }
// handle second player here because of switch statement falltrough //
        if (type == FULL_CLIENT_LOCAL) {
            clients.at(1)->connect(password);
        }
        isRunning = true;
    } else {
        isRunning = false;
    }
    return isRunning;
}

void UI::Networker::getLastState(Core::GameState & gs) {
    // stuff //
    switch (type) {
        case FULL_CLIENT_LOCAL:
        case FULL_CLIENT:
            if (server) {
                server->getLastState(gs);
            }
        case SIMPLE_CLIENT:
            clients.at(0)->getLastState(gs);
    }
}



