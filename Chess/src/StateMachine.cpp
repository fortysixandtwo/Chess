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



#include "StateMachine.h"
#include <string>

Core::StateMachine::StateMachine() {
    uiState.type = PREMATCH;
    uiState.chatbuffer = "";

    networkState.type = INIT_NETWORK;
    networkState.msg = "";
}

bool Core::StateMachine::iterate() {
    bool hasStateChanged = false;
    if (completedTasks) {
        // do something //
    }


    return hasStateChanged;
}


// XXX Task Management // 

uint32_t Core::StateMachine::getNewTaskId() {
    return tasks.at(tasks.size()-1).id +1;
}

uint32_t Core::StateMachine::addTask(action_t action) {
    return addTask(action.type, action.msg);
}
uint32_t Core::StateMachine::addTask(action_type_t type, const std::string & msg) {
    task_t newTask;
    uint32_t id = getNewTaskId();

    newTask.id = id;
    newTask.action.msg = msg;
    newTask.action.type = type;
    newTask.isActive = true;
    newTask.isWaiting = true;
    newTask.requiresPlayerInteraction = false;

    tasks.push_back(newTask);

    return id;
}



bool Core::StateMachine::completeTask(uint32_t id, const std::string & in_msg, \
    std::string & out_msg) {

    bool taskCompleted = false;
    for (int i=0;i<tasks.size();++i) {
        if (tasks.at(i).id == id) {
            if (tasks.at(i).isActive) {
                if (tasks.at(i).isWaiting) {
                    tasks.at(i).isWaiting = false;
                }
                tasks.at(i).isActive = false;
                taskCompleted = true;
                break;
            }
        }
    }

    return taskCompleted;
}
