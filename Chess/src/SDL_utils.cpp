/*****
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



#include "SDL_utils.h"


// SDL functions for rendering, loading textures, etc //
namespace SDL {
    void logSDLError(std::ostream & os, const std::string & msg) {
        os << msg << " Error: " << SDL_GetError() << std::endl;
    }

    void logSDLNetError(std::ostream & os, const std::string & msg) {
        os << msg << " Error: " << SDLNet_GetError() << std::endl;
    }

    SDL_Texture * loadTexture(const std::string & file, SDL_Renderer * ren) {
        SDL_Texture * texture = IMG_LoadTexture(ren, file.c_str());
        if (texture == nullptr) {
            logSDLError(std::cout, "IMG_LoadTexture");
        }
        return texture;
    }

    void renderTexture(SDL_Texture * tex, SDL_Renderer * ren,
            SDL_Rect * dst, SDL_Rect * clip) {
        SDL_RenderCopy(ren, tex, clip, dst);
    }

    void renderTexture(SDL_Texture * tex, SDL_Renderer * ren,
            int x, int y, SDL_Rect * clip) {

        SDL_Rect dst;
        dst.x = x;
        dst.y = y;
        if (clip != nullptr) {
            dst.w = clip->w;
            dst.h = clip->h;
        }
        else {
            SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
        }
        renderTexture(tex, ren, &dst, clip);
    }

}
