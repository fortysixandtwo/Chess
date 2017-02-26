#include <SDL_net.h>
#include <SDL.h>
#include <iostream>
#include <string>

#include "SDL_utils.h"
#include "client.h"
#include "net_utils.h"
#include "GameState.h"

int main(int argc, char **argv) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL::logSDLError(std::cout, "SDL_Init");
        return 1;
    }
    if (SDLNet_Init() == -1) {
        SDL::logSDLNetError(std::cout, "SDLNet_Init");
        SDL_Quit();
    }
    std::string host = "Q";
    uint16_t port = 9999;
    std::string nickname = "debuger";
    std::string password = "sehr_geheim";
    Net::Client client = Net::Client(host, port, nickname, true, true);
    client.connect(password);
    SDL_Delay(100);
//    client.moveFigure(8, 0, 4);
    std::string coord1 = "A2";
    std::string coord2 = "A4";
    std::cout << "Trying move A2->A4" << std::endl;
    client.moveFigure(coord1, coord2);
    for (int i=0;i<20;++i) {
        SDL_Delay(1000);
    }
    client.disconnect();

    return 0;
}
        
