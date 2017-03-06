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



#ifndef VERSION_H
#define VERSION_H


#include <string>

#define V_MAJOR "0"
#define V_MINOR "1"
#define V_PATCH "0"

inline std::string getVersionString() {
    std::string version = "";
    version.append(V_MAJOR);
    version.append(".");
    version.append(V_MINOR);
    version.append(".");
    version.append(V_PATCH);
    return version;
}

#endif
