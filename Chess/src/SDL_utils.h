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



#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_net.h>
#include <SDL_ttf.h>
#include "cleanup.h"
#include <iostream>
#include <string>

namespace SDL {
    void logSDLError(std::ostream & os, const std::string & msg);
    void logSDLNetError(std::ostream & os, const std::string & msg);
    SDL_Texture * loadTexture(const std::string & file, SDL_Renderer * ren);
    void renderTexture(SDL_Texture * tex, SDL_Renderer * ren,
            SDL_Rect * dst, SDL_Rect * clip = nullptr);
    void renderTexture(SDL_Texture * tex, SDL_Renderer * ren,
            int x, int y, SDL_Rect * clip = nullptr);
}

#endif
