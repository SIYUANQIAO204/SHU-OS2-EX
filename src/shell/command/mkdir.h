<<<<<<< HEAD
//
// Created by qiao on 26-1-1.
//

#ifndef OS_MKDIR_H
#define OS_MKDIR_H
#include <utility>

#include "../command.h"
namespace command {
    class mkdir : public command {
    public:
        mkdir(std::shared_ptr<user::user> user1, std::shared_ptr<sys::sys> system, int pid, std::string command_name, std::vector<std::string > kernel) : command(std::move(user1), std::move(system), pid, std::move(command_name), std::move(kernel)){}
        int execute() override;
        ~mkdir() = default;
    };
}

#endif //OS_MKDIR_H
=======
//
// Created by qiao on 26-1-1.
//

#ifndef OS_MKDIR_H
#define OS_MKDIR_H
#include <utility>

#include "../command.h"
namespace command {
    class mkdir : public command {
    public:
        mkdir(std::shared_ptr<user::user> user1, std::shared_ptr<sys::sys> system, int pid, std::string command_name, std::vector<std::string > kernel) : command(std::move(user1), std::move(system), pid, std::move(command_name), std::move(kernel)){}
        int execute() override;
        ~mkdir() = default;
    };
}

#endif //OS_MKDIR_H
>>>>>>> 320bfbd07e519d91666d3598d3577053a0f562b8
