
//
// Created by qiao on 25-12-25.
//file类用于实现用户对于inode的访问，通过间接访问的方式增加安全性

#ifndef OS_FILE_H
#define OS_FILE_H
#pragma once

#include <fcntl.h>

#include <utility>
#include <string>
#include <memory>
#include "virtualinode.h"
#include "directory_inode.h"
#include "inode.h"
namespace file{
    class file : public std::enable_shared_from_this<file> {
    private:
        std::shared_ptr<inode> node;   // 指向文件 inode
        int offset;                    // 当前读写位置
        int flags;                     // 打开方式
        std::shared_ptr<file> father;//该文件所在的上一级目录
    public:
        file(std::shared_ptr<inode> Inode, std::shared_ptr<file> fa, int flags)
                : node(std::move(Inode)), father(std::move(fa)), offset(0), flags(flags) {}

        ~file() = default;

        void foo() {
            std::shared_ptr<file> self = shared_from_this();
            bar(self);
        }

        void bar(std::shared_ptr<file> p) {}

        /* ========= 读写接口 ========= */

        std::optional<std::vector<int>> read(int len) {
            //if (!(flags & O_RDONLY)) return std::nullopt;
            auto data = node->read(offset, len);
            if (data) offset += data->size();
            return data;
        }

        int write(std::vector<int> buf) {
            //if (!(flags & O_WRONLY)) return -1;
            int written = node->write(offset, buf, buf.size());
            if (written > 0) offset += written;
            return written;
        }

        /* ========= 控制接口 ========= */

        int seek(int pos) {//更改位置
            if (pos < 0) return -1;
            offset = pos;
            return offset;
        }

        std::shared_ptr<inode> getInode() const {
            return node;
        }

        std::shared_ptr<file> getFather() const {return father;}

        std::shared_ptr<file> createFile(int id,int user, std::shared_ptr<fileSystem> fsys,std::string name, InodeType type, std::shared_ptr<file> father_dir) {
            if(node->getINodeType() != InodeType::DIRECTORY) return nullptr;
            if(type == InodeType::VIRTUAL)
            {
                auto new_node = std::make_shared<virtualinode>(id,type,user,fsys,name);
                node->addInode(name, new_node);
                return std::make_shared<file>(node ,father_dir, 1);
            }
            else if(type == InodeType::DIRECTORY)
            {
                auto new_node = std::make_shared<directory_inode>(id,type,user,fsys,name);
                node->addInode(name, new_node);
                return std::make_shared<file>(node ,father_dir, 1);
            }
            return nullptr;
        }

        std::optional<std::vector<int>> deleteFile(std::string name){
            return node->deleteInode(std::move(name));
        }

        std::shared_ptr<inode> open(std::string name){
            auto rtb = node->openFile(name);
            return rtb;
        }

    };

}

#endif //OS_FILE_H

