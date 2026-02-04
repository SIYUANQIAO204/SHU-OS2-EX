//
// Created by qiao on 25-12-30.
//

#ifndef OS_FDTABLE_H
#define OS_FDTABLE_H
#include <utility>

#include "file.h"
#include "fileSystem.h"
#pragma once
#include "../user/user.h"
namespace file {
    class fdtable {
    private:
        std::vector<std::shared_ptr<file>> FCB;
        std::shared_ptr<user::user> cut_user;
        std::shared_ptr<fileSystem> file_system;
        int cut_file;
        std::shared_ptr<inode> root_dic;
    public:
        fdtable(std::shared_ptr<user::user> user1, std::shared_ptr<fileSystem> fsys) :cut_user(std::move(user1)), file_system(std::move(fsys)) {FCB = {}; cut_file = 0; root_dic = file_system->getRoot();}
        ~fdtable() = default;
        int openNewFile(std::string Directory  = "",int flag = 0, int pos = 0);
        int openFile(std::string name,int flag = 0, int pos = 0);
        int createFile(int id, InodeType type, std::string name);
        int write(const std::vector<int>& buf);
        int seek (int pos);
        std::optional<std::vector<int>> read(int len);
        int switchFile(int idx);
        int closefile();
        int deleteFile(std::string name);
        bool safetyCheck();
        std::shared_ptr<file> getFile() const {return FCB[cut_file];}
        int back();
    };
}

#endif //OS_FDTABLE_H
