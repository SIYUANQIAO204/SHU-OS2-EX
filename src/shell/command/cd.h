
//
// Created by qiao on 26-1-2.
//该指令用于创建文件或者文件夹，第一个参数为文件名称，第二个可选参数为文件路径，第三个可选参数为权限设定

#ifndef OS_CD_H
#define OS_CD_H
#include "../command.h"

namespace command {
    class cd  : public command{
    public:
        cd(std::shared_ptr<user::user> user1, std::shared_ptr<sys::sys> system, int pid, std::string command_name, std::vector<std::string > kernel) : command(std::move(user1), std::move(system), pid, std::move(command_name), std::move(kernel)){}
        int execute() override;
        ~cd() = default;
    };
}

#endif //OS_CD_H

