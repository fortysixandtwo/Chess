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


