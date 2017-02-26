#include "UIOptions.h"

#include <string>
#include "GameState.h"

UI::Options::Options() {
    //
    width = 800;
    height = 480;
    fullscreen = false;
    tilesize = 55;
    offset_chessboard_x = 20;
    offset_chessboard_y = 20;
    theme = "default";
    perspective = Core::BLACK;

}

UI::Options::Options(const Options & options) {
    //
    this->width = options.width;
    this->height = options.height;
    this->fullscreen = options.fullscreen;
    this->tilesize = options.tilesize;
    this->offset_chessboard_x = options.offset_chessboard_x;
    this->offset_chessboard_y = options.offset_chessboard_y;
    this->theme = options.theme;
    this->perspective = options.perspective;

}


