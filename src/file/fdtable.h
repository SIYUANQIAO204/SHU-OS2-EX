
//
// Created by qiao on 25-12-30.
//用户所持有的用于访问文件系统的表，包含了异常的反馈

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
        std::vector<std::shared_ptr<file>> FCB;//用户打开的所有文件
        std::shared_ptr<user::user> cut_user;//持有该fdtable的用户
        std::shared_ptr<fileSystem> file_system;//文件系统
        int cut_file;//打开的文件数量
        std::shared_ptr<inode> root_dic;//指向该用户的根目录
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

