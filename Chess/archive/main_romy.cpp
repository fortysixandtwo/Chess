#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_net.h>
#include "SDL_utils.h"
#include <iostream>
#include <string>
#include "res_path.h"
#include "cleanup.h"
#include "GameState.h"
#include "GameLogic.h"
#include "server.h"
#include "client.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
// Tile size: (480 - 32 - 8 ) / 8 //
const int CHESS_TILE_SIZE = 55;



// main program //
int main(int argc, char** argv) {
    // Create game state object //
    Game::GameState gs = Game::GameState();
    Game::GameLogic gl = Game::GameLogic();

//    std::cout << gl.getFigureOnTile(5,1) << std::endl;
    /***
    Net::Server serv = Net::Server(9999,"");
    serv.waitForClients();
    ***/
    std::cout << "Please enter nickname: ";
    std::string nickname;
    std::cin >> nickname;
    bool quit = false;
    std::string host = "Q";
    uint16_t port = 9999;
    Net::Client client = Net::Client(host, port, nickname);

    std::string password = "sehr_geheim";
    bool connected = client.connect(password);
    if (!connected) {
        std::cout << "Could not establish connection to " << host\
            << " on port " << port << std::endl << "Exiting..." << std::endl;
        quit = true;

    }

// SDL Initialization
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL::logSDLError(std::cout, "SDL_Init");
        SDL_Quit();
        return 1;
    }
    if (SDLNet_Init() == -1) {
        SDL::logSDLNetError(std::cout, "SDLNet_Init");
        SDL_Quit();
        return 1;
    }
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        SDL::logSDLError(std::cout, "IMG_Init");
        SDL_Quit();
        return 1;
    }
    SDL_Window * window = SDL_CreateWindow("Chess", 0, 0, SCREEN_WIDTH,
        SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL::logSDLError(std::cout, "SDL_CreateWindow");
        SDLNet_Quit();
        SDL_Quit();
        return 1;
    }
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        SDL::logSDLError(std::cout, "SDL_CreateRenderer");
        cleanup(window);
        SDLNet_Quit();
        SDL_Quit();
        return 1;
    }

// Resource Path for Textures of chess pieces etc //
    const std::string resPath = getResourcePath("Chess");
    SDL_Texture * background[3];
    background[0] = SDL::loadTexture(resPath + "bg_white.png", renderer);
    background[1] = SDL::loadTexture(resPath + "bg_black.png", renderer);
    background[2] = SDL::loadTexture(resPath + "background.png", renderer);
    SDL_Texture * textures[12];
    // textures[0-5] contains white pieces //
    // textures[6-11] contains black pieces //
    textures[0] = SDL::loadTexture(resPath + "rook_white.png", renderer);
    textures[1] = SDL::loadTexture(resPath + "knight_white.png", renderer);
    textures[2] = SDL::loadTexture(resPath + "bishop_white.png", renderer);
    textures[3] = SDL::loadTexture(resPath + "queen_white.png", renderer);
    textures[4] = SDL::loadTexture(resPath + "king_white.png", renderer);
    textures[5] = SDL::loadTexture(resPath + "pawn_white.png", renderer);
    textures[6] = SDL::loadTexture(resPath + "rook_black.png", renderer);
    textures[7] = SDL::loadTexture(resPath + "knight_black.png", renderer);
    textures[8] = SDL::loadTexture(resPath + "bishop_black.png", renderer);
    textures[9] = SDL::loadTexture(resPath + "queen_black.png", renderer);
    textures[10] = SDL::loadTexture(resPath + "king_black.png", renderer);
    textures[11] = SDL::loadTexture(resPath + "pawn_black.png", renderer);

    SDL_Event e;
// Main SDL loop
    while (!quit) {
// Event handling loop //
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        SDL_RenderClear(renderer);
// Render background //
        SDL::renderTexture(background[2], renderer, 0, 0);
        int x,y;
        int tilesize = 55;
        int offset_chessboard_x = 20;
        int offset_chessboard_y = 20;
        for (uint8_t i = 0; i < 8; ++i) {
            x = tilesize*i + offset_chessboard_x;
            for (uint8_t j = 0; j < 8; ++j) {
                // Checkerboard
                y=tilesize*j + offset_chessboard_y;
                int bw_choice = (i+j)%2;
                SDL::renderTexture(background[bw_choice], renderer, x, y);
            }

        }
// Render active chess pieces //
        for (uint8_t i=0;i<32;++i) {
            if (gs.figures[i].isAlive) {
                x = offset_chessboard_x + \
                    tilesize*gs.figures[i].posx;
                y = offset_chessboard_y + \
                    tilesize*gs.figures[i].posy;
                int texture_index = gs.figures[i].figure + \
                    6*gs.figures[i].team;
                SDL::renderTexture(textures[texture_index], renderer, x, y);
            }
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(25);
// Check gamestate and render pieces at their position
    }
// Cleanup and Exit

    cleanup(textures[0], textures[1], textures[2], textures[3], 
            textures[4], textures[5], textures[6], textures[7],
            textures[8], textures[9], textures[10], textures[11],
            background[1], renderer, window);

    IMG_Quit();
    SDLNet_Quit();
    SDL_Quit();
    return 0;
}
