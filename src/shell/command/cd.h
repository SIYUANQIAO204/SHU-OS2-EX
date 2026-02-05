<<<<<<< HEAD
//
// Created by qiao on 26-1-2.
//

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
=======
//
// Created by qiao on 26-1-2.
//

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
>>>>>>> 320bfbd07e519d91666d3598d3577053a0f562b8
