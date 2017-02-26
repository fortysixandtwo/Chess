#ifndef COREUTILS_H
#define COREUTILS_H

#include <string>



namespace Core {
    const std::string MOVE_DELIMITER = "->";

    std::string coordinatesToChess(uint8_t posx, uint8_t posy);
    bool coordinatesFromChess( \
        const std::string & coords, uint8_t * posx, uint8_t * posy\
    );
//    bool isOnBoard(const std::string & coords);
    bool isOnBoard(uint8_t posx, uint8_t posy);
    bool isMoveStringCorrect(std::string & moveString);


}


#endif
