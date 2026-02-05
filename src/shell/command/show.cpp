//
// Created by qiao on 26-1-2.
//

#include "show.h"
namespace command{
    int show::execute() {
        auto table = system->getFDTable(cmd_user->getUid());
        table->getFile()->getInode()->showInfo();
        return 1;
    }
}