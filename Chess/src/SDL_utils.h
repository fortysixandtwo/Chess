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
