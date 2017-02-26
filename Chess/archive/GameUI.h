#ifndef GameUI_H
#define GameUI_H

#include <SDL.h>
#include "GameLogic.h"
#include "client.h"
#include "server.h"

namespace UI {

    class GameManager {
// The game manager consists mainly of the following 3 Objects //
// which deal with the //
// rendering of the UI, everything network and event Handling on the UI //
// Networking should be done in a separate thread for it not to interfere //
// with the targetUPS/FPS //

        private:
            Renderer renderer;
            Networker networker;
            EventHandler eventHandler;

// Game specific //
            Game::GameLogic gameLogic;
            bool quit;
            int targetUPS;

        public:
            GameManager(int targetUPS = 30);
            mainLoop();

    };

    class Renderer {
        private:
// SDL specific //
            SDL_Window * window;
            SDL_Renderer * renderer;
            SDL_Texture * background;
            SDL_Texture * textures;
// UI Stuff //
            std::string resPath;
// Use resDefaultPath as a fallback when ressources are not available //
// in the directory of the theme in use //
            std::string resDefaultPath;
            options_t optionsUi;
            bool isInitialized;


            bool initializeSDL();
            bool loadResources();
        public:
            Renderer();
            bool init();
            void setOptions(optionsUi);

            void renderOnce();
            void registerPreRenderHook();
            void registerPostRenderHook();

           

    };

    class Networker {
        private:
            std::vector<Net::Client> clients;
            bool isServerRunning;
            Net::Server server;

        public:
            bool addClient(Net::Client & client);
            bool startServer();



    };

    class EventHandler {
        private:
            SDL_event event;

    };

    struct options_t {
        int tilesize;
        int offset_chessboard_x;
        int offset_chessboard_y;
        std::string theme;
    };
/*
    enum state_t {
        INIT,
}
*/



#endif
