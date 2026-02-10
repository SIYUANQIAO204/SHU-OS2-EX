
//
// Created by qiao on 25-12-27.
//用于管理所有的inode的管理器

#ifndef OS_INODEMANAGER_H
#define OS_INODEMANAGER_H
#include "inode.h"
#include "virtualinode.h"
#include <unordered_map>
#include "directory_inode.h"
namespace file {
    class inodeManager {
    private:
        std::vector<std::shared_ptr<inode>> inodes;//所有inode的指针
        std::unordered_map<int,int> nodeId2idx;//id到下标的映射
        std::vector<int> inode_Ids;//所有inode的id
        std::shared_ptr<directory_inode> root_directory;//系统根目录
        int inode_num;//inode的数量
    public:
        ~inodeManager() = default;
        void init(const std::shared_ptr<directory_inode>& root);
        int createVInode(int id, int owner, std::string name, std::weak_ptr<fileSystem> file_sys);
        int createDirectory(int id, int owner, std::weak_ptr<fileSystem> file_sys, std::string name);
        int inodeid2Idx(int id) const;
        std::shared_ptr<inode> getInode(int idx) {return inodes[idx];};
        int getNodeOwnerId(int id) const;
        std::optional<Permission> getNodePermission(int id) const;
        std::optional<std::string> getNodeName(int id) const;
        std::optional<std::pair<int, int>> getNodeIdfromDirectory(int directory, std::string name) const;
        int write(int id, int pos, std::vector<int> buf, int len);
        std::optional<std::vector<int>> read(int id, int pos, int len);
        int deleteData(int id, int pos, int len);
        int deleteOneData(int id, int pos);
        int deleteINode(int id);
        int addInode(std::shared_ptr<inode> node);
    };
}

#endif //OS_INODEMANAGER_H

