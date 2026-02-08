
//
// Created by qiao on 26-1-2.
//shell的函数实现

#include "shell.h"
namespace shell{
    int shell::run() {
        std::string line;
        std::getline(std::cin, line);

        std::istringstream input(line);
        return cmdPhatser->ProcessCmd(input);
    }

    void shell::update() {
        cut_user = cmdPhatser->getUser();
    }
}