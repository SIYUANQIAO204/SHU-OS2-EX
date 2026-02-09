//
// Created by qiao on 26-1-2.
//该指令实现向文件结尾追加内容

#include "append.h"
namespace command{
    int append::execute() {
        auto table = system->getFDTable(cmd_user->getUid());
        table->seek(table->getFile()->getInode()->getSize()-1);
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