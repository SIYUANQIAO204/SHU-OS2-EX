
//
// Created by qiao on 26-1-2.
//该指令用于读取从当前文件指针开始的一段内容，第一个参数为起始点，第二个参数为长度

#ifndef OS_READ_H
#define OS_READ_H


#include "../command.h"
namespace command {
    class read : public command {
    public:
        read(std::shared_ptr<user::user> user1, std::shared_ptr<sys::sys> system, int pid, std::string command_name, std::vector<std::string > kernel) : command(std::move(user1), std::move(system), pid, std::move(command_name), std::move(kernel)){}
        int execute() override;
        ~read() = default;
    };
}


#endif //OS_READ_H

