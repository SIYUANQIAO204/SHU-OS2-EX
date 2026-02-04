//
// Created by qiao on 26-1-1.
//

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
