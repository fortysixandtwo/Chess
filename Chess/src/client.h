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
