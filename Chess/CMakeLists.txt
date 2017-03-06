#
#This file is part of SDL-Chess.
#
#    SDL-Chess is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    SDL-Chess is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with SDL-Chess.  If not, see <http://www.gnu.org/licenses/>.
#
#



project(Chess)
find_package(SDL2_image REQUIRED)
find_package(SDL2_net REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${SDL2_NET_INCLUDE_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIR})
add_executable(Chess 
    src/main.cpp src/GameState.cpp src/GameLogic.cpp src/GameManager.cpp
    src/server.cpp src/client.cpp src/SDL_utils.cpp src/net_utils.cpp
    src/UIRender.cpp src/Networker.cpp src/EventHandler.cpp src/StateMachine.cpp
    src/core_utils.cpp src/UIOptions.cpp
    )
add_executable(ChessServ 
    src/server.cpp src/test_server.cpp src/SDL_utils.cpp src/net_utils.cpp
    src/core_utils.cpp src/GameLogic.cpp src/GameState.cpp
    )
add_executable(ChessClient
    src/client.cpp src/test_client.cpp src/SDL_utils.cpp src/net_utils.cpp
    src/core_utils.cpp src/GameLogic.cpp src/GameState.cpp
    )
target_link_libraries(Chess 
    ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} 
    ${SDL2_NET_LIBRARY} ${SDL2_TTF_LIBRARY}
    )
target_link_libraries(ChessServ 
    ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} 
    ${SDL2_NET_LIBRARY} ${SDL2_TTF_LIBRARY}
    )
target_link_libraries(ChessClient
    ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} 
    ${SDL2_NET_LIBRARY} ${SDL2_TTF_LIBRARY}
    )
install(TARGETS Chess RUNTIME DESTINATION ${BIN_DIR})
install(TARGETS ChessServ RUNTIME DESTINATION ${BIN_DIR})
install(TARGETS ChessClient RUNTIME DESTINATION ${BIN_DIR})
