
//
// Created by qiao on 26-1-1.
//指令基类，包含构造，析构以及执行函数，构造参数包括指令名字，指令参数
//目前command不具有图灵完备性
//不是很熟具体指令，部分指令的名称直接用英文单词了

#ifndef OS_COMMAND_H
#define OS_COMMAND_H
#include <utility>

#include "memory"

#include "../sys/sys.h"
#pragma once
namespace command{
    class command{
    protected:
        std::shared_ptr<user::user> cmd_user;
        std::shared_ptr<sys::sys> system;
        int pid;
        std::string cwd;
        std::vector<std::string> kernel;
    public:
        command(std::shared_ptr<user::user> user1, std::shared_ptr<sys::sys> system, int pid, std::string command_name, std::vector<std::string > kernel)
            : cmd_user(std::move(user1)), system(system), pid(pid), cwd(std::move(command_name)), kernel(std::move(kernel)) {}
        virtual ~command() = default;
        virtual  int execute() = 0;
    };
}
#endif //OS_COMMAND_H
