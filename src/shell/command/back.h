//
// Created by qiao on 26-1-3.
//

#ifndef OS_BACK_H
#define OS_BACK_H


#include "../command.h"
namespace command {
    class back : public command{
    public:
        back(std::shared_ptr<user::user> user1, std::shared_ptr<sys::sys> system, int pid, std::string command_name, std::vector<std::string > kernel) : command(std::move(user1), std::move(system), pid, std::move(command_name), std::move(kernel)){}
        int execute() override;
        ~back() = default;
    };
}


#endif //OS_BACK_H
