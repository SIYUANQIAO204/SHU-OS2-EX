
//
// Created by qiao on 26-1-2.
//该指令实现向文件尾部追加内容

#ifndef OS_APPEND_H
#define OS_APPEND_H
#include "../command.h"
namespace command {
    class append : public command{
    public:
        append(std::shared_ptr<user::user> user1, std::shared_ptr<sys::sys> system, int pid, std::string command_name, std::vector<std::string > kernel) : command(std::move(user1), std::move(system), pid, std::move(command_name), std::move(kernel)){}
        int execute() override;
        ~append() = default;

    };
}

#endif //OS_APPEND_H

