
//
// Created by qiao on 26-1-2.
//

#include "read.h"
namespace command{
    int read::execute() {
        auto table = system->getFDTable(cmd_user->getUid());
        int st = 0, len = table->getFile()->getInode()->getSize();
        if((int) kernel.size() >=1){
            try {
                int x = std::stoi(kernel[0]);
            } catch (const std::invalid_argument&) {
                std::cout<<"非法输入\n";
                return -1;
            } catch (const std::out_of_range&) {
                std::cout<<"非法输入\n";
                return -1;
            }
            len = std::stoi(kernel[0]);
        }
        if((int) kernel.size() >= 2){
            try {
                int x = std::stoi(kernel[1]);
            } catch (const std::invalid_argument&) {
                std::cout<<"非法输入\n";
                return -1;
            } catch (const std::out_of_range&) {
                std::cout<<"非法输入\n";
                return -1;
            }
            st = std::stoi(kernel[1]);
            table->seek(st);
        }
        auto outcome = table->read(len);
        if(outcome == std::nullopt){
            std::cout<<"非法访问\n";
            return -1;
        }
        for(auto p : *outcome){
            std::cout<<p<<' ';
        }
        std::cout<<'\n';
        return 1;
    }
}