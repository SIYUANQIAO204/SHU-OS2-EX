
//
// Created by qiao on 26-1-2.
//这是shell部分，理论上为整个项目的最顶层的面向用户的结构，包含了当前用户，系统以及指令编译器

#ifndef OS_SHELL_H
#define OS_SHELL_H
#include "commandPharser.h"
namespace shell {
    class shell {
    private:
        std::shared_ptr<user::user> cut_user;
        std::shared_ptr<sys::sys> system;
        std::shared_ptr<command::commandPharser> cmdPhatser;
        int proecess;
    public:
        shell(std::shared_ptr<user::user> log_user, std::shared_ptr<sys::sys> sys1,int process) : cut_user(log_user), system(sys1), proecess(process){
            cmdPhatser = std::make_shared<command::commandPharser>(cut_user,system,process);
        }
        ~shell() = default;
        void update();//用于更新系统的状态
        int run();
    };
}

#endif //OS_SHELL_H

