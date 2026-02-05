//
// Created by qiao on 25-12-27.
//

#include "inodeManager.h"

#include <utility>
namespace file{

    int inodeManager::inodeid2Idx(int id) const {
        auto it = nodeId2idx.find(id);
        return (it != nodeId2idx.end()) ? it->second : -1;
    }

    void inodeManager::init(const std::shared_ptr<directory_inode>& root) {
        inode_Ids.push_back(root->getNodeID());
        nodeId2idx[root->getNodeID()] = inode_num;
        inode_num = 1;
        inodes.push_back(root);
        root_directory = root;
    }

    std::optional<std::vector<int>> inodeManager::read(int id, int pos, int len) {
        int idx = inodeid2Idx(id);
        if(idx == -1) return std::nullopt;
        return inodes[idx]-> read(pos,len);
    }

    int inodeManager::getNodeOwnerId(int id) const {
        int idx = inodeid2Idx(id);
        if(idx == -1) return -1;
        return  inodes[idx]->getOwnerID();
    }

    int inodeManager::deleteData(int id, int pos, int len) {
        int idx = inodeid2Idx(id);
        if(idx == -1) return -1;
        return inodes[idx]->deleteData(pos, len);
    }

    int inodeManager::createDirectory(int id, int owner, std::weak_ptr<fileSystem> file_sys, std::string name) {
        nodeId2idx[id] = inode_num;
        inode_Ids.push_back(id);
        inodes.push_back(std::make_shared<directory_inode>(id,InodeType::DIRECTORY,owner,file_sys,name));
        inode_num++;
        return 1;
    }

    int inodeManager::deleteINode(int id) {
        int idx = inodeid2Idx(id);
        if (idx == -1) return -1;
        inode_Ids.erase(inode_Ids.begin()+idx);
        inodes.erase(inodes.begin()+idx);
        for (auto &kv : nodeId2idx) {
            if (kv.second > idx) {
                kv.second--;
            }
        }
        inode_num--;
        return 1;
    }

    std::optional<std::pair<int, int>> inodeManager::getNodeIdfromDirectory(int directory, std::string name) const {
        int idx = inodeid2Idx(directory);
        if(idx == -1) return std::nullopt;
        int dir_size = inodes[idx]->getSize();
        auto inodes_id_under_diretory = inodes[idx]->read(0,dir_size);
        if(inodes_id_under_diretory == std::nullopt) return std::nullopt;
        for (int i = 0; i < dir_size; i++)
        {
            if(inodes[inodes_id_under_diretory->operator[](i)]->getName() == name)
            {
                return std::make_pair(inodes[inodes_id_under_diretory->operator[](i)]->getNodeID(),i);
            }
        }
        return std::nullopt;
    }

    int inodeManager::createVInode(int id, int owner, std::string name, std::weak_ptr<fileSystem> file_sys) {
        nodeId2idx[id] = inode_num;
        inode_Ids.push_back(id);
        inodes.emplace_back(std::make_shared<virtualinode>(id,InodeType::VIRTUAL,owner,file_sys,name));
        inode_num++;
        return 1;
    }

    int inodeManager::deleteOneData(int id, int pos) {
        int idx = inodeid2Idx(id);
        if(idx == -1) return -1;
        return inodes[idx]->deleteData(pos,1);
    }

    int inodeManager::write(int id, int pos, std::vector<int> buf, int len) {
        int idx = inodeid2Idx(id);
        if(idx == -1) return -1;
        return inodes[idx]->write(pos, std::move(buf), len);
    }

    std::optional<Permission> inodeManager::getNodePermission(int id) const {
        int idx = inodeid2Idx(id);
        if( idx == -1) return std::nullopt;
        return inodes[idx]->getPremission();
    }

    std::optional<std::string> inodeManager::getNodeName(int id) const {
        int idx = inodeid2Idx(id);
        if( idx == -1) return std::nullopt;
        return inodes[idx]->getName();
    }

    int inodeManager::addInode(std::shared_ptr<inode> node) {
        nodeId2idx[node->getNodeID()] = inode_num;
        inode_Ids.push_back(node->getNodeID());
        inodes.emplace_back(node);
        inode_num++;
        return 1;
    }

}