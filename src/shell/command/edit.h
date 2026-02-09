
//
// Created by qiao on 26-1-2.
//用于实现任意位置的编辑文本，第一个参数如果以p开头则为指定起始位置，否则从文件当前指针的位置开始，剩余参数为输入内容

#ifndef OS_EDIT_H
#define OS_EDIT_H
#include "../command.h"
namespace command {
    class edit : public command{
    public:
        edit(std::shared_ptr<user::user> user1, std::shared_ptr<sys::sys> system, int pid, std::string command_name, std::vector<std::string > kernel) : command(std::move(user1), std::move(system), pid, std::move(command_name), std::move(kernel)){}
        int execute() override;
        ~edit() = default;
    };
}

#endif //OS_EDIT_H

