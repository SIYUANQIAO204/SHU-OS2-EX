<<<<<<< HEAD
//
// Created by qiao on 26-1-2.
//
#include "src/shell/shell.h"
#include "src/VirtualProcess/VirtualProcess.h"
#include "src/VirtualProcess/ProcessGenerater.h"
int main(){
    std::shared_ptr<sys::sys> system = std::make_shared<sys::sys>();
    for(int i = 0;i < 4;i++)
    {
        system->addResource(10);
    }
    for(int i=0;i<2;i++)
    {
        system->addProceeManager(PCB_Sta::clock);
        system->addProceeManager(PCB_Sta::prio);
    }
    system->init();
    auto process_generator = VP::RandomProcessGenerator(1024);
    std::shared_ptr<shell::shell> shell = std::make_shared<shell::shell>(system->getUserByUID(1),system,1);
    auto temp = process_generator.generateRandomProcessParams(
            0, 16, 1024*10, 5, 4, 4,
            10, 4);
    system->creatProcess(temp.pid, temp.prio, temp.memory, temp.time_needed, temp.Blocknum, temp.strategy,
                         temp.max_needed, 0, temp.CPU);
    while (true){
        shell->run();
        shell->update();
    }
    return 0;
=======
//
// Created by qiao on 26-1-2.
//
#include "src/shell/shell.h"
#include "src/VirtualProcess/VirtualProcess.h"
#include "src/VirtualProcess/ProcessGenerater.h"
int main(){
    std::shared_ptr<sys::sys> system = std::make_shared<sys::sys>();
    for(int i = 0;i < 4;i++)
    {
        system->addResource(10);
    }
    for(int i=0;i<2;i++)
    {
        system->addProceeManager(PCB_Sta::clock);
        system->addProceeManager(PCB_Sta::prio);
    }
    system->init();
    auto process_generator = VP::RandomProcessGenerator(1024);
    std::shared_ptr<shell::shell> shell = std::make_shared<shell::shell>(system->getUserByUID(1),system,1);
    auto temp = process_generator.generateRandomProcessParams(
            0, 16, 1024*10, 5, 4, 4,
            10, 4);
    system->creatProcess(temp.pid, temp.prio, temp.memory, temp.time_needed, temp.Blocknum, temp.strategy,
                         temp.max_needed, 0, temp.CPU);
    while (true){
        shell->run();
        shell->update();
    }
    return 0;
>>>>>>> 320bfbd07e519d91666d3598d3577053a0f562b8
}