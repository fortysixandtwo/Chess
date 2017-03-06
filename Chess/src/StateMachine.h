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



#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#define STATUS_MSG_BUFFER_SIZE 512
// Use net_utils packet size sth?

#include <string>
#include <vector>

namespace Core {
    enum action_type_t {
        FIGURE_SELECT, FIGURE_SELECT_RELEASE, FIGURE_SHOW_MOVES, \
        FIGURE_SHOW_MOVES_RELEASE, FIGURE_MOVE, CHAT_MSG, DISPLAY_SERVER_MSG, \
        FORFEIT, CHECKMATE, STALEMATE, REMATCH, INIT, QUIT, NONE
    };
    struct action_t {
        action_type_t type;
        std::string msg;
    };
    enum status_ui_type_t {
        PREMATCH, TURN_WHITE=0, TURN_BLACK=1, POSTMATCH, ALARM_TIME, INIT_UI
    };
    struct status_ui_t {
        status_ui_type_t type;
        std::string chatbuffer;
    };

    //enum action_network_t {
    //    CHAT, MOVE
    //};
    enum status_network_type_t {
        SEND, SEND_COMPLETE, SEND_FAILED, RECEIVE, RECEIVE_COMPLETE, \
        RECEIVE_FAILED, STALLED, HOST_DOWN, INIT_NETWORK
    };
    struct status_network_t {
        status_network_type_t type;
        std::string msg;
        
    };
    

    enum task_type_t {
        RENDER_UPDATE, NETWORK_IN, NETWORK_OUT, UI_IN, UI_OUT, \
        LOGIC_VALIDATE, LOGIC_MOVE
    };
    // This list of tasks is to be used by the GameManager in order //
    // to decide what to do in each update //
    // Actual structure prone to change //
    struct task_t {
        uint32_t id;
        action_t action;
        bool isActive;
        bool isWaiting;
        bool requiresPlayerInteraction;
    };

    class StateMachine {
        private:
            status_ui_t uiState;
            status_network_t networkState;
            std::vector<Core::task_t> tasks;
            bool completedTasks;

            uint32_t getNewTaskId();
            

        public:
            StateMachine();
// Returns whether the state changed (in other words: if a task completed) //
            bool iterate(); 
            uint32_t addTask(action_t action);
            uint32_t addTask( 
                action_type_t type, const std::string & msg 
                );
            /***
            uint32_t addNetworkingTask( 
                action_t type, const std::string & msg 
                );
            ***/
            bool completeTask( 
                uint32_t id, const std::string & in_msg, std::string & out_msg
                );
    };
}

#endif
