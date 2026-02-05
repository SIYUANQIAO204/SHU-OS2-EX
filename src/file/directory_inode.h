<<<<<<< HEAD
//
// Created by qiao on 25-12-28.
//

#ifndef OS_DIRECTORY_INODE_H
#define OS_DIRECTORY_INODE_H
#pragma once
#include "inode.h"
namespace file {
    class directory_inode : public inode {
    public:
        directory_inode(int id,InodeType Type,int owner, std::weak_ptr<fileSystem> file_sys, std::string name) : inode(id,Type,owner, std::move(file_sys), std::move(name)){}
        ~directory_inode() override = default;
        std::optional<std::vector<int>> read(int pos, int len) override {return std::nullopt;};
        int write(int pos, std::vector<int> buf, int len) override {return -1;}
        int getBlockPos (int lbn) override {return -1;}
        int allocateBlock(int num) override {return -1;}
        void appendBlcok(int idx) override {}
        int deleteData(int pos, int len) override {return -1;};
        std::vector<int> release() override {return {};};
        int addInode(std::string name, std::shared_ptr<inode> node) override;
        std::optional<std::vector<int>> deleteInode(std::string delete_name) override;
        std::shared_ptr<inode> openFile(std::string name) override;
        void showInfo() override;
    };
}

#endif //OS_DIRECTORY_INODE_H
=======
//
// Created by qiao on 25-12-28.
//

#ifndef OS_DIRECTORY_INODE_H
#define OS_DIRECTORY_INODE_H
#pragma once
#include "inode.h"
namespace file {
    class directory_inode : public inode {
    public:
        directory_inode(int id,InodeType Type,int owner, std::weak_ptr<fileSystem> file_sys, std::string name) : inode(id,Type,owner, std::move(file_sys), std::move(name)){}
        ~directory_inode() override = default;
        std::optional<std::vector<int>> read(int pos, int len) override {return std::nullopt;};
        int write(int pos, std::vector<int> buf, int len) override {return -1;}
        int getBlockPos (int lbn) override {return -1;}
        int allocateBlock(int num) override {return -1;}
        void appendBlcok(int idx) override {}
        int deleteData(int pos, int len) override {return -1;};
        std::vector<int> release() override {return {};};
        int addInode(std::string name, std::shared_ptr<inode> node) override;
        std::optional<std::vector<int>> deleteInode(std::string delete_name) override;
        std::shared_ptr<inode> openFile(std::string name) override;
        void showInfo() override;
    };
}

#endif //OS_DIRECTORY_INODE_H
>>>>>>> 320bfbd07e519d91666d3598d3577053a0f562b8
