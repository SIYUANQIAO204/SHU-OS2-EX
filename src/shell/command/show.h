//
// Created by qiao on 26-1-2.
//

#ifndef OS_SHOW_H
#define OS_SHOW_H

#include "../command.h"

namespace command {
    class show  : public command{
    public:
        show(std::shared_ptr<user::user> user1, std::shared_ptr<sys::sys> system, int pid, std::string command_name, std::vector<std::string > kernel) : command(std::move(user1), std::move(system), pid, std::move(command_name), std::move(kernel)){}
        int execute() override;
        ~show() = default;
    };
}


#endif //OS_SHOW_H
