
//
// Created by qiao on 25-12-27.
//

#include "fileSystem.h"
namespace file{
    int fileSystem::read_data(int idx, int pos) {
        return file_block_Manager->read(idx,pos);
    }

    std::optional<std::vector<int>> fileSystem::read_data(int idx, int beg, int ed) {
        return file_block_Manager->read(idx, beg, ed);
    }

    void fileSystem::write(int idx, int pos, int data) {
        file_block_Manager->write(idx, pos, data);
    }

    void fileSystem::write(int idx, int beg, int ed, std::vector<int> data, int data_beg) {
        file_block_Manager->write(idx, beg, ed, data, data_beg);
    }

    void fileSystem::delete_block_data(int idx, int beg, int ed) {
        file_block_Manager->deleteData(idx, beg, ed);
    }

    std::optional<std::vector<int>> fileSystem::allocateBlock(int num) {
        return file_block_Manager->allocateBlock(num);
    }

    int fileSystem::allocateOneBlock() {
        return file_block_Manager->allocateBlock(1)->front();
    }

    void fileSystem::getAvailableBlock(std::vector<int> fBlock) {
        file_block_Manager->getAvailableBlock(fBlock);
    }

    void fileSystem::deleteINode(int id) {
        inode_manager->deleteINode(id);
    }

    int fileSystem::createVInode(int id, int owner, std::string name) {
        auto sp = std::make_shared<fileSystem>();
        sp->foo();
        return inode_manager->createVInode(id, owner, std::move(name), sp);
    }

    int fileSystem::createDirectory(int id, int owner, std::string name) {
        auto sp = shared_from_this();
        return inode_manager->createDirectory(id, owner, sp, std::move(name));
    }


    void fileSystem::setroot() {//设置根目录
        createDirectory(0,0,"home");
        root = inode_manager->getInode(0);
    }

    int fileSystem::addInode(std::shared_ptr<inode> node) {
        return inode_manager->addInode(node);
    }

}