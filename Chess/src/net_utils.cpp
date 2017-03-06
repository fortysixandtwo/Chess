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



#include "net_utils.h"
#include <SDL_net.h>
#include <SDL.h>
#include <string>
#include <iostream>

#define MAX_RETRIES 10

namespace Net {
    bool send(UDPsocket udpsock, IPaddress * address, \
        request_t request, std::string & msg) {
        bool success = true;
        UDPpacket * packet = SDLNet_AllocPacket(PACKETSIZE);
        // data: Request+msg+0
        int datalen = msg.size()+2;
        packet->address.host = address->host;
        packet->address.port = address->port;
        packet->len = datalen;
        uint8_t data[PACKETSIZE];
        data[0] = request;
        for (uint16_t i=0;i<msg.size();++i) {
            data[1+i] = msg.at(i);
        }
        data[1+msg.size()] = 0;
        memcpy(packet->data, data, datalen*sizeof(uint8_t));

//        std::cout << "msg: " << msg << std::endl;

        if (SDLNet_UDP_Send(udpsock, -1, packet) == 0) {
            SDL::logSDLNetError(std::cout, "SDLNet_UDP_Send");
            success = false;
        }
        return success;
    }

    bool recv(UDPsocket udpsock, IPaddress * address, \
        request_t * request, std::string * msg) {
        bool success = false;
        UDPpacket * packet = SDLNet_AllocPacket(PACKETSIZE);
        int numrecv;
        numrecv = SDLNet_UDP_Recv(udpsock, packet);
        if (numrecv > 0) {
            *request = (request_t)packet->data[0];
            char * c_msg = new char[packet->len];
            for (uint16_t i=0;i<packet->len;++i) {
                c_msg[i] = packet->data[1+i];
            }
            *msg = std::string(c_msg);
            delete[] c_msg;
            memcpy(address, &(packet->address), sizeof(IPaddress));
            success = true;
        } else if (numrecv == -1) {
            SDL::logSDLNetError(std::cout, "SDLNet_UDP_Recv");
        }
        SDLNet_FreePacket(packet);
        return success;
    }

    bool sendAndReceive(UDPsocket udpsock, IPaddress * address, \
        request_t outrequest, std::string & outMsg, request_t *inrequest, \
        std::string * inMsg, int delayRetry, bool verbose) {

        bool success = false;
        int retries = 0;

        while ((!success) && (retries < MAX_RETRIES)) {
            if (send(udpsock, address, outrequest, outMsg)) {
                SDL_Delay(delayRetry);
                if (recv(udpsock, address, inrequest, inMsg)) {
                    success = true;
                }
            }
            ++retries;
        }

        if (success) {
            if (*inrequest == INVALID) {
                if (verbose) {
                    std::cout << "Requested action was unsuccessful." << std::endl;
                    std::cout << "::" << *inMsg << std::endl;
                }
                success = false;
            } else if (*inrequest != VALID) {
                if (verbose) {
                    std::cout << "::Server sent gibberish!" << std::endl;
                }
                success = false;
            }
        }

        return success;
    }

}
