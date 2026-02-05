//
// Created by qiao on 26-1-2.
//

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
