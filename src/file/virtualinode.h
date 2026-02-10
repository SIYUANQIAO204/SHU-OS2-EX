
//
// Created by qiao on 25-12-25.
//本文件类型实现的是模拟文件，用于模拟对实际文件的各种操作

#ifndef OS_VIRTUALINODE_H
#define OS_VIRTUALINODE_H
#pragma once
#include "inode.h"

#include <utility>
#include <optional>
namespace file {
    class virtualinode : public inode {
    public:
        virtualinode(int id,InodeType Type,int owner, std::weak_ptr<fileSystem> file_sys, std::string name) : inode(id,Type,owner, std::move(file_sys),std::move(name)){}
        ~virtualinode() override = default;
        std::optional<std::vector<int>> read(int pos, int len) override;
        int write(int pos, std::vector<int> buf, int len) override;
        int getBlockPos (int lbn) override;
        int allocateBlock(int num) override;
        void appendBlcok(int idx) override;
        int deleteData(int pos, int len) override;//用于删除从pos开始长len的数据
        std::vector<int> release() override;
        int addInode(std::string name, std::shared_ptr<inode> node) override { return -1;}
        std::optional<std::vector<int>> deleteInode(std::string delete_name) override;//只能用于自我删除
        std::shared_ptr<inode> openFile(std::string name) override {return nullptr;};
        void showInfo() override;//展示全部的文本内容
    };
}

#endif //OS_VIRTUALINODE_H
