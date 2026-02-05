//
// Created by qiao on 26-1-2.
//

#include "Open.h"
namespace command{
    int open::execute() {
        auto table = system->getFDTable(cmd_user->getUid());
        if(table == nullptr) return -1;
        if((int) kernel.size() < 1){
            std::cout<<"请输入要打开的文件名称\n";
            return -1;
        }
        std::string name = kernel[0];
        int flag = 3;
        if((int) kernel.size() >= 2){
            try {
                int x = std::stoi(kernel[1]);
            } catch (const std::invalid_argument&) {
                std::cout<<"非法输入\n";
                return -1;
            } catch (const std::out_of_range&) {
                std::cout<<"非法输入\n";
                return -1;
            }
            flag = std::stoi(kernel[1]);
        }

        return table->openFile(name,flag);
    }
}