
//
// Created by qiao on 26-1-2.
//

#include "login.h"
namespace command{
    int login::execute() {
        if((int) kernel.size() < 2){
            std::cout<<"参数错误，请输入用户名和密码\n";
            return -1;
        }
        if(system->login(system->getUserIdbyName(kernel[0]),kernel[1]))
        {
            return 1;
        } else{
            std::cout<<"用户名或密码错误\n";
            return -1;
        }
    }

}