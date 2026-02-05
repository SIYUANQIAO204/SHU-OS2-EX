<<<<<<< HEAD
//
// Created by qiao on 26-1-2.
//

#ifndef OS_COMMANDPHARSER_H
#define OS_COMMANDPHARSER_H
#include "command/append.h"
#include "command/cd.h"
#include "command/edit.h"
#include "command/login.h"
#include "command/mkdir.h"
#include "command/read.h"
#include "command/show.h"
#include "command/Open.h"
#include "command/rm.h"
#include "command/back.h"
namespace command {
    class commandPharser {
    private:
        std::shared_ptr<user::user> cmd_user;
        int pid;
        std::shared_ptr<sys::sys> system;
    public:
        commandPharser(std::shared_ptr<user::user> cmd_user, std::shared_ptr<sys::sys> sys1,int process) : cmd_user(cmd_user), system(sys1), pid(process) {}
        ~commandPharser() = default;
        int ProcessCmd(std::istream &input);
        std::shared_ptr<user::user> getUser() const {return cmd_user;}
    };
}

#endif //OS_COMMANDPHARSER_H
=======
//
// Created by qiao on 26-1-2.
//

#ifndef OS_COMMANDPHARSER_H
#define OS_COMMANDPHARSER_H
#include "command/append.h"
#include "command/cd.h"
#include "command/edit.h"
#include "command/login.h"
#include "command/mkdir.h"
#include "command/read.h"
#include "command/show.h"
#include "command/Open.h"
#include "command/rm.h"
#include "command/back.h"
namespace command {
    class commandPharser {
    private:
        std::shared_ptr<user::user> cmd_user;
        int pid;
        std::shared_ptr<sys::sys> system;
    public:
        commandPharser(std::shared_ptr<user::user> cmd_user, std::shared_ptr<sys::sys> sys1,int process) : cmd_user(cmd_user), system(sys1), pid(process) {}
        ~commandPharser() = default;
        int ProcessCmd(std::istream &input);
        std::shared_ptr<user::user> getUser() const {return cmd_user;}
    };
}

#endif //OS_COMMANDPHARSER_H
>>>>>>> 320bfbd07e519d91666d3598d3577053a0f562b8
