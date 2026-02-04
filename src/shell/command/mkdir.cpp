//
// Created by qiao on 26-1-1.
//

#include "mkdir.h"
namespace command{
    int mkdir::execute() {
        auto table = system->getFDTable(cmd_user->getUid());
        if(kernel.empty()){
            std::cout<<"参数错误，至少需要输入名字\n";
            return -1;
        }
        std::string name = kernel[0];
        std::string dir = cmd_user->getHomeDir();
        int sit = 1;
        if((int) kernel.size() >= 2){
            dir += kernel[1];
            sit = table->openNewFile(dir,2);
        }
        if(sit == -1){
            return -1;
        }
        sit = table->createFile(system->getNewFileID(), file::InodeType::DIRECTORY,name);
        if(sit == -1){
            return -1;
        }
        table->openFile(name,2);
        if((int) kernel.size() >= 3)
        {
            if(kernel[2] == "private"){
                table->getFile()->getInode()->setPremission(file::Permission::PRIVATE);
            }
            else if(kernel[2] == "public"){
                table->getFile()->getInode()->setPremission(file::Permission::PUBLIC);
            }
        }
        return 1;
    }
}