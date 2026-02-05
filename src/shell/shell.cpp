<<<<<<< HEAD
//
// Created by qiao on 26-1-2.
//

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
=======
//
// Created by qiao on 26-1-2.
//

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
>>>>>>> 320bfbd07e519d91666d3598d3577053a0f562b8
}