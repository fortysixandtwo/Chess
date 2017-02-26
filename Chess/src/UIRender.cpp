#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "UIRender.h"
#include "UIOptions.h"
#include "SDL_utils.h"
#include "res_path.h"
#include "cleanup.h"
#include "StateMachine.h"
#include "core_utils.h"


bool UI::Renderer::initializeSDL() {
    // TODO Use SDL_WasInit etc first //
    bool success = false;
 // SDL Initialization
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        SDL::logSDLError(std::cout, "IMG_Init");
        SDL_Quit();
        return 1;
    }
    window = SDL_CreateWindow("Chess", 0, 0, uiOptions.width,
        uiOptions.height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL::logSDLError(std::cout, "SDL_CreateWindow");
        SDLNet_Quit();
        SDL_Quit();
        return 1;
    }
    if (uiOptions.fullscreen) {
        if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN) != 0) {
            std::cout << "Could set window to fullscreen" << std::endl;
        }
    }
    renderer = SDL_CreateRenderer(window, -1,
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

SDL_Texture * UI::Renderer::loadTexture(const std::string & fname) {
    // fname should be a string containing the filename //
    // Returns true if file found in either themed or default directory //
    // Falls back to default directory in the second case //
    // Returns false if file not found //
    SDL_Texture * texture = SDL::loadTexture(resPath + fname, renderer);
    if (texture == nullptr) {
        std::cout << "fack" << std::endl;
    }
    return texture;
}
    

bool UI::Renderer::loadResources() {
    bool success = true;

    cleanTextures();

    background[0] = loadTexture("bg_white.png");
    background[1] = loadTexture("bg_black.png");
    background[2] = loadTexture("background.png");
    background[3] = loadTexture("bg_move.png");
    background[4] = loadTexture("bg_attack.png");

    // textures[0-5] contains white pieces //
    // textures[6-11] contains black pieces //
    // The Order is important for the rendering to render the right pieces //
    // texture index is gs.figures[i].figure = 6* gs.figures[i].team //

    textures[0] = loadTexture("rook_white.png");
    textures[1] = loadTexture("knight_white.png");
    textures[2] = loadTexture("bishop_white.png");
    textures[3] = loadTexture("queen_white.png");
    textures[4] = loadTexture("king_white.png");
    textures[5] = loadTexture("pawn_white.png");
    textures[6] = loadTexture("rook_black.png");
    textures[7] = loadTexture("knight_black.png");
    textures[8] = loadTexture("bishop_black.png");
    textures[9] = loadTexture("queen_black.png");
    textures[10] = loadTexture("king_black.png");
    textures[11] = loadTexture("pawn_black.png");


    // Check if all textures were correctly loaded //
    for (uint8_t i=0;i<12;++i) {
        if (textures[i] == nullptr) {
            success = false;
            std::cout << "texture[" << (int)i << "] == nullptr :/" << std::endl;
            break;
        }
    }
    if (!success) {
        cleanTextures();
    } else {
        loadedTextures = true;
    }

    return success;
}

bool UI::Renderer::init() {
    bool success = false;
    if (initializeSDL()) {
        success = loadResources();
    }
    isInitialized = success;
    actionHandled = success;
    action.type = Core::NONE;
    action.msg = "";
    return success;
}

void UI::Renderer::setOptions(Options & uiOptions) {
    this->uiOptions = uiOptions;
}

UI::Options UI::Renderer::getOptions() const {
    return uiOptions;
}

bool UI::Renderer::setAction(Core::action_t action) {
    bool actionSet = false;
    std::cout << "setting " << action.type \
        << " " << action.msg;
    if (actionHandled) {
        this->action.type = action.type;
        this->action.msg = action.msg;
        actionSet = true;
        std::cout << " check!";
    }
    std::cout << std::endl;
    return actionSet;
}

bool UI::Renderer::handleAction() {
    if (action.type != Core::NONE) {
        std::cout << "handling the action! " \
            << action.type << std::endl;
        actionHandled = true;
    }
    switch (action.type) {
        case Core::FIGURE_SELECT:
            showFigure = true;
            break;
        case Core::FIGURE_SELECT_RELEASE:
            showFigure = false;
            break;
        case Core::FIGURE_SHOW_MOVES:
            showFigure = true;
            showFigureMove = true;
            break;

        case Core::FIGURE_SHOW_MOVES_RELEASE:
            showFigure = false;
            showFigureMove = false;
            break;
        default:
            break;
    }
    if ((action.type == Core::FIGURE_SELECT) \
        || (action.type == Core::FIGURE_SHOW_MOVES)) {
        Core::coordinatesFromChess(action.msg, &selectedx, &selectedy);
    }
    return actionHandled;
}


UI::Renderer::Renderer() {
// Set default options for rendering //
    uiOptions = Options();

    resPath = getResourcePath("Chess/" + uiOptions.theme);
    isInitialized = false;
    loadedTextures = false;
    showFigure = false;
    showFigureMove = false;
    actionHandled = false;
    selectedx = 0;
    selectedy = 0;
    action.type = Core::INIT;
    action.msg = "";
//    std::cout << "Created UIRender object" << std::endl;
}

void UI::Renderer::renderOnce(const Core::GameState & gs) {
    if (!isInitialized) {
        std::cout << "Trying to render, but renderer not initialized." << std::endl;
        exit(1);
    }
    SDL_RenderClear(renderer);
// Render background //
    SDL::renderTexture(background[2], renderer, 0, 0);
    int x,y;
    for (uint8_t i = 0; i < 8; ++i) {
        x = uiOptions.tilesize*i + uiOptions.offset_chessboard_x;
        for (uint8_t j = 0; j < 8; ++j) {
            // Checkerboard
            y=uiOptions.tilesize*j + uiOptions.offset_chessboard_y;
            int bw_choice = (i+j)%2;
            SDL::renderTexture(background[bw_choice], renderer, x, y);
        }

    }
    if (showFigure) {
//        std::cout << "Showing figure!" << std::endl;
        // take perspective into acount
//        if (Core::coordinatesFromChess(action.msg, &posx, &posy)) {
        if (Core::isOnBoard(selectedx, selectedy)) {
            if (uiOptions.perspective == Core::BLACK) {
                x = uiOptions.offset_chessboard_x + \
                    uiOptions.tilesize * (7-selectedx);
                y = uiOptions.offset_chessboard_y + \
                    uiOptions.tilesize * selectedy;
            } else {
                x = uiOptions.offset_chessboard_x + \
                    uiOptions.tilesize * selectedx;
                y = uiOptions.offset_chessboard_y + \
                    uiOptions.tilesize * (7-selectedy);
            }
            SDL::renderTexture(background[3], renderer, x, y);
        }
    }
    if (showFigureMove) {
        //get valid moves and render them

    }
// Render active chess pieces //
    for (uint8_t i=0;i<32;++i) {
        if (gs.figures[i].isAlive) {
            x = uiOptions.offset_chessboard_x + \
                uiOptions.tilesize*gs.figures[i].posx;
            if ((uiOptions.perspective == Core::WHITE) \
                || (uiOptions.perspective == Core::SPECTATOR)) {
                y = uiOptions.offset_chessboard_y + \
                    uiOptions.tilesize*gs.figures[i].posy;
            } else {
                y = uiOptions.offset_chessboard_y + \
                    uiOptions.tilesize*(7-gs.figures[i].posy);
            }

            int texture_index = gs.figures[i].figure + \
                6*gs.figures[i].team;
            SDL::renderTexture(textures[texture_index], renderer, x, y);
        }
    }
    SDL_RenderPresent(renderer);
}




void UI::Renderer::cleanTextures() {
    if (loadedTextures) {
        std::cout << "Freeing texture memory." << std::endl;
        cleanup(textures[0], textures[1], textures[2], textures[3], 
            textures[4], textures[5], textures[6], textures[7],
            textures[8], textures[9], textures[10], textures[11],
            background[1]);
    }
    loadedTextures = false;
}

void UI::Renderer::cleanWindow() {
    cleanup(renderer, window);
}


void UI::Renderer::cleanUp() {
    cleanTextures();
    cleanWindow();
}

