#include "UIRenderer.h"
//#include "UINetworker.h"
//#include "UIEventHandler.h"

namespace UI {

    class GameManager {
// The game manager consists mainly of the following 3 Objects //
// which deal with the //
// rendering of the UI, everything network and event Handling on the UI //
// Networking should be done in a separate thread for it not to interfere //
// with the targetUPS/FPS //

        private:
            Renderer renderer;
//            Networker networker;
//            EventHandler eventHandler;

// Game specific //
            Game::GameLogic gameLogic;
            bool quit;
            int targetUPS;

        public:
            GameManager(int targetUPS = 30);
            mainLoop();

    };

}
