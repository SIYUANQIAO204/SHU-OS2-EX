//
// Created by qiao on 26-1-2.
//

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
