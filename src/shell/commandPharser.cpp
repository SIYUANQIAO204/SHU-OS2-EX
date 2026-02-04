//
// Created by qiao on 26-1-2.
//

#include "commandPharser.h"
namespace command{
    int commandPharser::ProcessCmd(std::istream &input) {
        std::string cmd_name;
        if(!(input >> cmd_name)){
            std::cout<<"未输入任何指令\n";
            return -1;
        }
        std::vector<std::string> kenerl;
        std::string ken;
        while(input >> ken) kenerl.emplace_back(ken);
        if(cmd_name == "append"){
            auto cmd = std::make_shared<append>(cmd_user, system, pid, cmd_name, kenerl);
            return cmd->execute();
        } else if(cmd_name == "cd"){
            auto cmd = std::make_shared<cd>(cmd_user,system,pid,cmd_name,kenerl);
            return cmd->execute();
        }else if(cmd_name == "edit"){
            auto cmd = std::make_shared<edit>(cmd_user,system,pid,cmd_name,kenerl);
            return cmd->execute();
        } else if(cmd_name == "login"){
            auto cmd = std::make_shared<login>(cmd_user, system, pid, cmd_name,kenerl);
            if(cmd->execute() == 1){
                cmd_user = system->getUserByUID(system->getUserIdbyName(kenerl[0]));
                return 1;
            }
            return -1;
        } else if(cmd_name == "mkdir"){
            auto cmd = std::make_shared<mkdir>(cmd_user,system,pid,cmd_name,kenerl);
            return cmd->execute();
        } else if(cmd_name == "read"){
            auto cmd = std::make_shared<read>(cmd_user,system,pid,cmd_name,kenerl);
            return cmd->execute();
        } else if(cmd_name == "show"){
            auto cmd = std::make_shared<show>(cmd_user,system,pid,cmd_name,kenerl);
            return cmd->execute();
        } else if(cmd_name == "open"){
            auto cmd = std::make_shared<open>(cmd_user,system,pid,cmd_name,kenerl);
            return cmd->execute();
        } else if(cmd_name == "rm"){
            auto cmd = std::make_shared<rm>(cmd_user,system,pid,cmd_name,kenerl);
            return cmd->execute();
        } else if(cmd_name == "back") {
            auto cmd = std::make_shared<back>(cmd_user,system,pid,cmd_name,kenerl);
            return cmd->execute();
        }
        else {
            std::cout<<"无效指令\n";
            return -1;
        }
    }
}