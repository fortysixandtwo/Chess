/*****
Copyright (C) 2017 Evangelos Ribeiro Tzaras

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



#ifndef UI_RENDER_H
#define UI_RENDER_H


#include <SDL.h>
#include "GameState.h"
#include "UIOptions.h"
#include "StateMachine.h"

namespace UI {

    
    class Renderer {
        private:

// SDL specific //
            SDL_Window * window;
            SDL_Renderer * renderer;
            SDL_Texture * background[5];
            SDL_Texture * textures[12];

// UI Resources and Initialisation //

// Use resDefaultPath as a fallback when ressources are not available //
// in the directory of the theme in use //
            std::string resPath;
            std::string resDefaultPath;
            Options uiOptions;
            bool isInitialized;
            bool loadedTextures;

// Everything about what to render
            Core::action_t action;
            bool actionHandled;
            bool showFigure;
            bool showFigureMove;
            uint8_t selectedx;
            uint8_t selectedy;


// Private functions
            bool initializeSDL();
            SDL_Texture * loadTexture(const std::string & fname);
            bool loadResources();
            void cleanTextures();
            void cleanWindow();
        public:
            Renderer();
            bool init();
            void setOptions(Options & uiOptions);
            UI::Options getOptions() const;

            bool setAction(Core::action_t action);
            bool handleAction();

            void renderOnce(const Core::GameState & gs);
            void registerPreRenderHook();
            void registerPostRenderHook();

            void cleanUp();

           

    };

}


#endif
