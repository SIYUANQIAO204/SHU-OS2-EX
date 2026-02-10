
//
// Created by qiao on 25-12-30.
//

#include "fdtable.h"
namespace file{
    //读写
    int fdtable::write(const std::vector<int> &buf) {
        if(!safetyCheck())
        {
            return -1;
        }
        if(FCB[cut_file]->write(buf) == -1){
            std::cerr<<"file write fail\n";
            return -1;
        }
        return 1;
    }

    std::optional<std::vector<int>> fdtable::read(int len) {
        if(!safetyCheck())
        {
            return std::nullopt;
        }
        auto ret = FCB[cut_file]->read(len);
        if(ret == std::nullopt){
            std::cout<<"非法访问\n";
            return std::nullopt;
        }
        return ret;
    }

    int fdtable::closefile() {//关闭一个打开的文件表
        FCB.erase(FCB.begin()+cut_file);
        if((int) FCB.size() > 0){
            cut_file = 0;
            return 1;
        }else{
            cut_file = -1;
            return 0;
        }
    }

    bool fdtable::safetyCheck() {//合法访问检测
        if( cut_file > (int) FCB.size())
        {
            std::cout<<"检测到非法访问，已自动回退到第一个打开文件\n";
            cut_file = 0;
        }
        if((int) FCB.size() == 0)
        {
            std::cout<<"无打开文件，请打开一个文件\n";
            return false;
        }
        return true;
    }

    int fdtable::createFile(int id, InodeType type, std::string name) {//在当前目录下创建并打开文件，id指的是文件id
        auto new_file = FCB[cut_file]->createFile(id, cut_user->getUid(),file_system,name,type, FCB[cut_file]);
        if(new_file == nullptr){
            std::cout<<"创建文件失败\n";
            return -1;
        }
        FCB.emplace_back(new_file);
        return 1;
    }

    int fdtable::deleteFile(std::string name) {//删除文件，不过删除当前文件会导致当前file悬空
        auto buf = FCB[cut_file]->deleteFile(name);
        if(buf == std::nullopt) {
            std::cout<<"删除失败\n";
            return -1;
        }
        return 1;
    }

    int fdtable::openFile(std::string name, int flag, int pos) {//在当前的file下打开一个文件
        auto new_file = FCB[cut_file]->open(std::move(name));
        int i = 1;
        if(new_file == nullptr){
            std::cout<<"文件不存在，无法打开\n";
            return -1;
        }
        FCB[cut_file] = std::make_shared<file>(new_file,FCB[cut_file],flag);
        FCB[cut_file]->seek(pos);
        return 1;
    }

    int fdtable::openNewFile(std::string Directory, int flag, int pos) {//在一个新的file下打开一个文件
        root_dic = file_system->getRoot();
        std::vector<std::string> Dic = {};
        std::string temp_buf = "";
        for(int i = 0; i< (int) Directory.size();i++)
        {
            if(Directory[i] !='/') temp_buf+=Directory[i];
            else{
                Dic.emplace_back(temp_buf);
                temp_buf = "";
            }
        }
        Dic.emplace_back(temp_buf);
        cut_file = (int) FCB.size();
        FCB.emplace_back(std::make_shared<file>(root_dic, nullptr,flag));
        for(int i =1 ;i < (int) Dic.size()-1;i++)
        {
            int sta = openFile(Dic[i],flag,pos);
            if(sta == -1){
                closefile();
                return -1;
            }
        }
        return 1;
    }

    int fdtable::switchFile(int idx) {//切换file
        if(idx >= (int) FCB.size()){
            std::cout<<"switch fail\n";
            return -1;
        }
        cut_file = idx;
        return 1;
    }

    int fdtable::seek(int pos) {
        if(pos >= FCB[cut_file]->getInode()->getSize()){
            std::cout<<"超出文件大小\n";
            return -1;
        }
        FCB[cut_file]->seek(pos);
        return 1;
    }

    int fdtable::back() {//回退至上级目录
        FCB[cut_file] = FCB[cut_file]->getFather();
        return 1;
    }

}