#include <string>


#include "GameUI.h"
#include "cleanup.h"
#include "res_path.h"


UI::GameManager::GameManager(int targetUPS) {
    // targetUPS is used to control the timing of the main loop //
    self->targetUPS = targetUPS;
    quit = false;
    renderer = Renderer();
    networker = Networker();
    eventHandler = eventHandler();

    gameLogic = Game::GameLogic();
}

void mainLoop() {
    while (!quit) {
        renderOnce(gameLogic.gs);
        SDL_Delay(25);
    }
}
/***
std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();

std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() <<std::endl;
std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() <<std::endl;
***/


// XXX Rendering //


bool UI::GameManager::initializeSDL() {
// TODO Use SDL_WasInit etc first //
// Modularize Initialization //
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL::logSDLError(std::cout, "SDL_Init");
        SDL_Quit();
        return success;
    }
    if (SDLNet_Init() == -1) {
        SDL::logSDLNetError(std::cout, "SDLNet_Init");
        SDL_Quit();
        return success;
    }
}

bool UI::Renderer::initializeSDL() {
    // TODO Use SDL_WasInit etc first //
    bool success = false;
 // SDL Initialization
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        SDL::logSDLError(std::cout, "SDL_CreateRenderer");
        cleanup(window);
        SDLNet_Quit();
        SDL_Quit();
        return success;
    }
    success = true;
    return success;
}

bool UI::Render::loadTexture(SDL_Texture * texture, std::string & fname) {
    // fname should be a string containing the filename //
    // Returns true if file found in either themed or default directory //
    // Falls back to default directory in the second case //
    // Returns false if file not found //
    texture = SDL::loadTexture(resPath + fname, renderer);
    return true;
}
    

bool UI::Render::loadResources() {
    bool success = true;
// Resource Path for Textures of chess pieces etc //
    SDL_Texture * background[3];

    background[0] = SDL::loadTexture(resPath + "bg_white.png", renderer);
    background[1] = SDL::loadTexture(resPath + "bg_black.png", renderer);
    background[2] = SDL::loadTexture(resPath + "background.png", renderer);
    SDL_Texture * textures[12];
    // textures[0-5] contains white pieces //
    // textures[6-11] contains black pieces //
    // The Order is important for the rendering to render the right pieces //
    // texture index is gs.figures[i].figure = 6* gs.figures[i].team //

    loadTexture(texture[0], "rook_white.png");
    loadTexture(texture[1], "knight_white.png");
    loadTexture(texture[2], "bishop_white.png");
    loadTexture(texture[3], "queen_white.png");
    loadTexture(texture[4], "king_white.png");
    loadTexture(texture[5], "pawn_black.png");
    loadTexture(texture[6], "rook_black.png");
    loadTexture(texture[7], "knight_black.png");
    loadTexture(texture[8], "bishop_black.png");
    loadTexture(texture[9], "queen_black.png");
    loadTexture(texture[10], "king_black.png");
    loadTexture(texture[11], "pawn_black.png");

/*
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
    */

    // Check if all textures were correctly loaded //
    for (uint8_t i=0;i<12;++i) {
        if (textures[i] == nullptr) {
            success = false;
            break;
        }
    }
    if (!success) {
        cleanup(

    return success;
}

bool UI::Render::init() {
    if (initializeSDL()) {
        return loadResources();
    }
    return false;
}

UI::Renderer::Renderer() {
// Set default options for rendering //
    optionsUi.width = 800;
    optionsUi.height = 480;
    optionsUi.tilesize = 55;
    optionsUi.offsetChessboardX = 20;
    optionsUi.offsetChessboardY = 20;
    optionsUi.theme = "default"
    optionsUi.fullscreen = false;

    resDefaultPath = getResourcePath("Chess/default");
    resPath = getResourcePath("Chess/" + optionsUi.theme;
    isInitialized = false;
    loadedTextures = false;
}

void UI::Render::renderOnce() {
    SDL_RenderClear(renderer);
// Render background //
    SDL::renderTexture(background[2], renderer, 0, 0);
    int x,y;
    for (uint8_t i = 0; i < 8; ++i) {
        x = optionsUI.tilesize*i + optionsUI.offset_chessboard_x;
        for (uint8_t j = 0; j < 8; ++j) {
            // Checkerboard
            y=optionsUI.tilesize*j + optionsUI.offset_chessboard_y;
            int bw_choice = (i+j)%2;
            SDL::renderTexture(background[bw_choice], renderer, x, y);
        }

    }
// Render active chess pieces //
    for (uint8_t i=0;i<32;++i) {
        if (gs.figures[i].isAlive) {
            x = optionsUI.offset_chessboard_x + \
                optionsUI.tilesize*gs.figures[i].posx;
            y = optionsUI.offset_chessboard_y + \
                optionsUI.tilesize*gs.figures[i].posy;
            int texture_index = gs.figures[i].figure + \
                6*gs.figures[i].team;
            SDL::renderTexture(textures[texture_index], renderer, x, y);
        }
    }
    SDL_RenderPresent(renderer);
}

void UI::Render::cleanTextures() {
    if (texturesLoaded) {
        cleanup(textures[0], textures[1], textures[2], textures[3], 
            textures[4], textures[5], textures[6], textures[7],
            textures[8], textures[9], textures[10], textures[11],
            background[1]);
    }
}

void UI::Render::cleanWindow() {
    cleanup(renderer, window);
}


void UI::Render::cleanUp() {
    cleanTextures();
    cleanWindow();
}

