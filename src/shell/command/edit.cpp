
//
// Created by qiao on 26-1-2.
//

#include "edit.h"
namespace command{
    int edit::execute() {
        auto table = system->getFDTable(cmd_user->getUid());
        if(kernel.empty()){
            return 1;
        }
        if(kernel[0][0] == 'p')
        {
            int pos = 0;
            for(int i = 1; i < (int) kernel.size();i++)
            {
                pos += kernel[0][i]-'0';
            }
            table->seek(pos);
        }
        std::vector<int> buf;
        for(auto p:kernel)
        {
            try {
                int x = std::stoi(p);
            } catch (const std::invalid_argument&) {
                std::cout<<"非法输入\n";
                return -1;
            } catch (const std::out_of_range&) {
                std::cout<<"非法输入\n";
                return -1;
            }
            int x = std::stoi(p);
            buf.emplace_back(x);
        }
        table->write(buf);
        return 1;
    }
}