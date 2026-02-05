//
// Created by qiao on 25-12-25.
//

#ifndef OS_INODE_H
#define OS_INODE_H
#pragma once

#include <cstring>
#include <string>
#include <utility>
#include <vector>
#include "memory"
#include "optional"
#include "fsconst.h"
namespace file{
    enum class InodeType {
        VIRTUAL,    // 普通文件（模拟）
        DIRECTORY,  // 目录
        DEVICE,     // 设备
        TXT
    };

    enum class Permission {
        PUBLIC,
        PRIVATE,
        INVISIBLE,
        BROKEN
    };


    class fileSystem;
    class inode;
    class Dentry {
    public:
        std::string name;
        std::weak_ptr<inode> inode;
    };

    class inode{
    protected:
        int inode_id;
        InodeType type;

        int size;
        int block_num;
        Permission perm;
        int owner_uid;
        std::string name;

        int direct[DIRECT_CNT];
        int single_indirect;
        int double_indirect;
        int cut_double_indirect_idx;
        int cut_double_indirect_pos;

        int read_count;
        bool writing;
        int ref_count;

        std::weak_ptr<fileSystem> file_system;
        std::vector<Dentry> dec;
    public:
        inode(int id, InodeType Type, int owner, std::weak_ptr<fileSystem> file_sys, std::string inode_name):
            inode_id(id), type(Type), owner_uid(owner), name(std::move(inode_name))  {
            file_system = std::move(file_sys);
            std::memset(direct,-1,sizeof(direct));
            block_num = 0;
            size = 0;
            single_indirect = -1;
            double_indirect = -1;
            cut_double_indirect_idx = 0;
            cut_double_indirect_pos = 0;
            ref_count = 0;
            read_count++;
            writing = false;
            dec = {};
        }
        virtual ~inode() = default;
        virtual std::optional<std::vector<int>> read(int pos, int len) = 0;
        virtual int write(int pos, std::vector<int> buf, int len) = 0;
        virtual int getBlockPos(int lbn) = 0;
        virtual int allocateBlock(int num) = 0;
        virtual void appendBlcok(int idx) = 0;
        Permission getPremission() const {return perm;}
        InodeType getINodeType() const {return type;}
        int getOwnerID() const {return owner_uid;}
        void setPremission(Permission new_prem) { perm = new_prem;}
        std::string getName() {return name;}
        virtual int deleteData(int pos, int len) = 0;
        int getNodeID() const {return inode_id;}
        int getSize() const {return size;}
        virtual std::vector<int> release() = 0;
        virtual int addInode(std::string name, std::shared_ptr<inode> node) = 0;
        virtual std::optional<std::vector<int>> deleteInode(std::string delete_name) = 0;
        virtual std::shared_ptr<inode> openFile(std::string name) = 0;
        void link() {ref_count++;}
        void unlink() {ref_count++;}
        virtual void showInfo() = 0;
    };
}
#endif //OS_INODE_H
