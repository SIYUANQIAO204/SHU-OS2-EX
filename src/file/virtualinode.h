<<<<<<< HEAD
//
// Created by qiao on 25-12-25.
//

#ifndef OS_VIRTUALINODE_H
#define OS_VIRTUALINODE_H
#pragma once
#include "inode.h"

#include <utility>
#include "optional"
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
        int deleteData(int pos, int len) override;
        std::vector<int> release() override;
        int addInode(std::string name, std::shared_ptr<inode> node) override { return -1;}
        std::optional<std::vector<int>> deleteInode(std::string delete_name) override;
        std::shared_ptr<inode> openFile(std::string name) override {return nullptr;};
        void showInfo() override;
    };
}

#endif //OS_VIRTUALINODE_H
=======
//
// Created by qiao on 25-12-25.
//

#ifndef OS_VIRTUALINODE_H
#define OS_VIRTUALINODE_H
#pragma once
#include "inode.h"

#include <utility>
#include "optional"
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
        int deleteData(int pos, int len) override;
        std::vector<int> release() override;
        int addInode(std::string name, std::shared_ptr<inode> node) override { return -1;}
        std::optional<std::vector<int>> deleteInode(std::string delete_name) override;
        std::shared_ptr<inode> openFile(std::string name) override {return nullptr;};
        void showInfo() override;
    };
}

#endif //OS_VIRTUALINODE_H
>>>>>>> 320bfbd07e519d91666d3598d3577053a0f562b8
