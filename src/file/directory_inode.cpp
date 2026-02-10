
//
// Created by qiao on 25-12-28.
//

#include "directory_inode.h"
#include "fileSystem.h"
#include <iostream>
namespace file {
    int directory_inode::addInode(std::string name, std::shared_ptr<inode> node) {
        if (file_system.expired()) {//检测指针分裂的调试用信息，正常使用不会出现
            std::cerr << "inode expired\n";
        }
        auto sp = file_system.lock();
        sp->addInode(node);
        dec.push_back(Dentry(name, node));
        size++;
        return 1;
    }

    std::optional<std::vector<int>> directory_inode::deleteInode(std::string delete_name) {
        if (ref_count > 1) return std::nullopt;
        if (delete_name == name) {//若删除的节点为自身，则会删除下属的全部文件
            for (auto p: dec) {
                auto sp = p.inode.lock();
                sp->link();
                auto temp_buffer = sp->deleteInode(p.name);
                if (temp_buffer == std::nullopt) {
                    return std::nullopt;
                } else if ((int) temp_buffer->size() == 0) continue;
                auto fsys = file_system.lock();
                fsys->getAvailableBlock(*temp_buffer);
            }
            auto sp = file_system.lock();
            sp->deleteINode(inode_id);
            return {};
        } else {//否则会遍历所有文件，查看是否有匹配的文件
            for (int i = 0; i < size; i++) {
                auto p = dec[i];
                if (p.name == delete_name) {
                    auto sp = p.inode.lock();
                    auto fsys = file_system.lock();
                    auto temp_buffer = sp->deleteInode(p.name);
                    if (temp_buffer == std::nullopt) {
                        return std::nullopt;
                    }
                    fsys->getAvailableBlock(*temp_buffer);
                    dec.erase(dec.begin() + i);
                    return {};
                }
            }
            return std::nullopt;
        }
    }

    std::shared_ptr<inode> directory_inode::openFile(std::string name) {//打开文件就是遍历寻找
        for (const auto &p: dec) {
            if (p.name == name) {
                if (p.inode.expired()) {
                    std::cerr << "inode expired\n";
                }
                return p.inode.lock();
            }
        }
        return nullptr;
    }

    void directory_inode::showInfo() {//展示文件夹内所有文件的名称
        for (auto p: dec) {
            std::cout << p.name << '\n';
        }
    }
}
