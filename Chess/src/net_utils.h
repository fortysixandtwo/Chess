#ifndef NET_UTILS_H
#define NET_UTILS_H

#include <string>
#include <SDL_net.h>
#include <iostream>
#include "SDL_utils.h"
#include "GameState.h"

#define PACKETSIZE 512

namespace Net {

    const std::string MSG_DELIMITER = ";";
    struct client_t {
        uint8_t id;
        std::string nickname;
        IPaddress address;
        Core::team_t team;
    };

    enum request_t { HELLO, CONNECT, DISCONNECT, VALID, INVALID, \
        GREET, MOVE, CHAT, REMATCH, SERVERMSG };

    inline std::string resolveAddress(IPaddress * address) {
        std::string add = std::string(SDLNet_ResolveIP(address));
        add = add + ":" + std::to_string(address->port);
        return add;
    }

    bool send(UDPsocket udpsock, IPaddress * address, \
        request_t request, std::string & msg);
    bool recv(UDPsocket udpsock, IPaddress * address, \
        request_t * request, std::string * msg);        
    bool sendAndReceive(UDPsocket udpsock, IPaddress * address, \
        request_t outrequest, std::string & outMsg, request_t *inrequest, \
        std::string * inMsg, int delayRetry, bool verbose = false);

}

#endif
