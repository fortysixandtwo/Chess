#ifndef UIOPTIONS_H
#define UIOPTIONS_H

#include <string>
#include "GameState.h"

namespace UI {
    
    class Options {
            
        public:
            int width;
            int height;
            bool fullscreen;
            int tilesize;
            int offset_chessboard_x;
            int offset_chessboard_y;
            std::string theme;
            Core::team_t perspective;

            Options();
            Options(const Options & options);

    };

}


#endif
