//
// Created by qiao on 25-12-30.
//

#include "fileManager.h"
namespace file{
    int fileManager::createFDTable(std::shared_ptr<user::user> login_user, std::shared_ptr<fileSystem> fsys) {
        uid2idx[login_user->getUid()] = (int) folder.size();
        folder.emplace_back(std::make_shared<fdtable>(login_user,fsys));
        return 1;
    }

    std::shared_ptr<fdtable> fileManager::switchFDTable(int uid){
        int idx = uidToIdx(uid);
        if(idx == -1){
            return nullptr;
        }
        return folder[idx];
    }

    int fileManager::deleteFDTable(int uid) {
        int idx = uidToIdx(uid);
        if(idx == -1){
            return -1;
        }
        folder.erase(folder.begin()+idx);
        uid2idx.erase(uid);
        for (auto &kv : uid2idx) {
            if (kv.second > idx) {
                kv.second--;
            }
        }
        return 1;
    }

    int fileManager::uidToIdx(int uid) const {
        auto it = uid2idx.find(uid);
        return (it != uid2idx.end()) ? it->second : -1;
    }
}