//
// Created by qiao on 25-12-27.
//

#ifndef OS_FILESYSTEM_H
#define OS_FILESYSTEM_H
#include "inode.h"
#include "fBlockManager.h"
#include "memory"
#include "inodeManager.h"
#pragma once
namespace file {
    class fileSystem : public std::enable_shared_from_this<fileSystem> {
    private:
        std::shared_ptr<fBlockManager> file_block_Manager;
        std::shared_ptr<inodeManager> inode_manager;
        std::shared_ptr<inode> root;
        int file_counter;
    public:
        void bar(std::shared_ptr<fileSystem> p) {}
        void foo() {
            std::shared_ptr<fileSystem> self = shared_from_this();
            bar(self);
        }

        fileSystem() {
            file_block_Manager = std::make_shared<fBlockManager>();
            inode_manager = std::make_shared<inodeManager>();
            file_counter = 0;

        }
        ~fileSystem() = default;
        int read_data(int idx,int pos);
        std::optional<std::vector<int>> read_data(int idx, int beg, int ed);
        void write(int idx,int beg,int ed, std::vector<int> data,int data_beg);
        std::optional<std::vector<int>> allocateBlock(int num);
        void write(int idx, int pos, int data);
        int allocateOneBlock();
        void delete_block_data(int idx,int beg, int ed);
        void getAvailableBlock(std::vector<int> fBlock);
        void deleteINode(int id);
        int createVInode(int id, int owner, std::string name);
        int createDirectory(int id, int owner, std::string name);
        int addInode(std::shared_ptr<inode> node);
        int allocateNewFileID()  {return file_counter++;}
        void setroot();
        std::shared_ptr<inode> getRoot() {return root;}
    };
}

#endif //OS_FILESYSTEM_H
