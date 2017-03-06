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



#include "server.h"
#include <SDL.h>
#include <SDL_net.h>
#include "SDL_utils.h"
#include <iostream>

int main() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL::logSDLError(std::cout, "SDL_Init");
        return 1;
    }
//    /**
    if (SDLNet_Init() == -1) {
        SDL::logSDLNetError(std::cout, "SDLNet_Init");
        SDL_Quit();
    }
//    **/
// /**
    Net::Server serv = Net::Server(9999, "sehr_geheim", true, true);
    serv.startServer();
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (!serv.listenForRequest()) {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
            }
            SDL_Delay(1);
        }
    }
//    **/
    /***
    UDPsocket udpsock;
    uint16_t portn;
    SDLNet_Write16(9999, &portn);
    udpsock = SDLNet_UDP_Open(portn);
    UDPpacket *packet = SDLNet_AllocPacket(512);
    SDL_Delay(5000);
    int numrecv;
    numrecv = SDLNet_UDP_Recv(udpsock, packet);
    std::cout << "numrecv: " << numrecv << std::endl;
    if (numrecv > 0) {
        std::cout << packet->len << std::endl;
        std::cout << packet->data << std::endl;
    }
    SDLNet_FreePacket(packet);
    SDLNet_UDP_Close(udpsock);
//    ***/
    SDLNet_Quit();
    SDL_Quit();
}
