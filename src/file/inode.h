
//
// Created by qiao on 25-12-25.
//定义了文件索引节点的内容，使用混合索引的方式
//目前设计的不太正规，理论上需要使用后端管理，但能力有限写不出来

#ifndef OS_INODE_H
#define OS_INODE_H
#pragma once

#include <cstring>
#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <optional>
#include "fsconst.h"
namespace file{
    enum class InodeType {
        VIRTUAL,    // 普通文件（模拟）
        DIRECTORY,  // 目录
        DEVICE,     // 设备
        TXT//文本
    };

    enum class Permission {
        PUBLIC,//公开的，任何用户都可以访问
        PRIVATE,//私密的，只有创建用户和管理员可以访问
        INVISIBLE,//隐藏的，只有管理员可以访问
        BROKEN//损坏的，无法访问
    };


    class fileSystem;//预声明管理所有节点和文件块的文件系统，让inode可以定义访问文件块的函数
    class inode;
    class Dentry {//目录用的表项，用于存储目录下的文件
    public:
        std::string name;//文件名字
        std::weak_ptr<inode> inode;//对应的索引节点
    };

    class inode{
    protected:
        int inode_id;//索引id
        InodeType type;//文件类型

        int size;//文件大小
        int block_num;//文件需要的块的数量
        Permission perm;//文件访问权限
        int owner_uid;//创建用户id
        std::string name;//文件名称

        int direct[DIRECT_CNT];//直接索引节点
        int single_indirect;//一级索引节点
        int double_indirect;//二级缩影节点
        int cut_double_indirect_idx;//当前二级索引节点的下标
        int cut_double_indirect_pos;//当前二级索引节点的位置
        //以下为用于文件共享的预留接口，并没有实际的相关应用
        int read_count;//正在读取该文件的用户数量
        bool writing;//有用户正在写入文件
        int ref_count;//文件目前的引用次数

        std::weak_ptr<fileSystem> file_system;//指向文件管理系统，用于读取文件
        std::vector<Dentry> dec;//文件所属的目录
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
        virtual int getBlockPos(int lbn) = 0;//获取文件块的位置
        virtual int allocateBlock(int num) = 0;//请求文件块
        virtual void appendBlcok(int idx) = 0;//在尾部追加文件块
        Permission getPremission() const {return perm;}//获取访问访问权限要求
        InodeType getINodeType() const {return type;}//获取文件类型
        int getOwnerID() const {return owner_uid;}//获取文件创建者
        void setPremission(Permission new_prem) { perm = new_prem;}
        std::string getName() {return name;}
        virtual int deleteData(int pos, int len) = 0;
        int getNodeID() const {return inode_id;}
        int getSize() const {return size;}
        virtual std::vector<int> release() = 0;
        virtual int addInode(std::string name, std::shared_ptr<inode> node) = 0;//文件夹文件用于增加节点
        virtual std::optional<std::vector<int>> deleteInode(std::string delete_name) = 0;//文件夹文件用于删除节点
        virtual std::shared_ptr<inode> openFile(std::string name) = 0;//文件夹文件用与打开文件夹下的文件
        //以下两个函数用于文件共享，但目前没有实际使用
        void link() {ref_count++;}//建立链接
        void unlink() {ref_count++;}//接触链接
        virtual void showInfo() = 0;
    };
}
#endif //OS_INODE_H
