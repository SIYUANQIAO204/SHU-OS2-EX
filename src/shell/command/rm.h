
//
// Created by qiao on 26-1-3.
//该指令用于删除文件，第一个参数为文件名称

#ifndef OS_RM_H
#define OS_RM_H

#include "../command.h"
namespace command {
    class rm : public command{
    public:
        rm(std::shared_ptr<user::user> user1, std::shared_ptr<sys::sys> system, int pid, std::string command_name, std::vector<std::string > kernel) : command(std::move(user1), std::move(system), pid, std::move(command_name), std::move(kernel)){}
        int execute() override;
        ~rm() = default;
    };
}


#endif //OS_RM_H

