<<<<<<< HEAD
//
// Created by qiao on 26-1-3.
//

#include "rm.h"
namespace command{
    int rm::execute() {
        if((int) kernel.size() < 1){
            std::cout<<"请输入要删除文件的名称\n";
            return -1;
        }
        std::string name = kernel[0];
        auto table = system->getFDTable(cmd_user->getUid());
        if(table == nullptr) return -1;
        return table->deleteFile(name);
    }
=======
//
// Created by qiao on 26-1-3.
//

#include "rm.h"
namespace command{
    int rm::execute() {
        if((int) kernel.size() < 1){
            std::cout<<"请输入要删除文件的名称\n";
            return -1;
        }
        std::string name = kernel[0];
        auto table = system->getFDTable(cmd_user->getUid());
        if(table == nullptr) return -1;
        return table->deleteFile(name);
    }
>>>>>>> 320bfbd07e519d91666d3598d3577053a0f562b8
}