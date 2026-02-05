<<<<<<< HEAD
//
// Created by qiao on 26-1-3.
//

#include "back.h"
namespace command{
    int back::execute() {
        auto table = system->getFDTable(cmd_user->getUid());
        if(table == nullptr) return -1;
        return table->back();
    }
=======
//
// Created by qiao on 26-1-3.
//

#include "back.h"
namespace command{
    int back::execute() {
        auto table = system->getFDTable(cmd_user->getUid());
        if(table == nullptr) return -1;
        return table->back();
    }
>>>>>>> 320bfbd07e519d91666d3598d3577053a0f562b8
}