
//
// Created by qiao on 25-12-30.
//管理所有用户的fdtable

#ifndef OS_FILEMANAGER_H
#define OS_FILEMANAGER_H
#include "fdtable.h"
namespace file {
    class fileManager {
    private:
        std::vector<std::shared_ptr<fdtable>> folder;
        std::unordered_map<int,int> uid2idx;//用户uid转下标
    public:
        fileManager()   {uid2idx = {};};
        ~fileManager() = default;
        int createFDTable(std::shared_ptr<user::user> login_user, std::shared_ptr<fileSystem> fsys);
        int uidToIdx(int uid) const;
        std::shared_ptr<fdtable> switchFDTable(int uid);
        int deleteFDTable(int uid);
    };
}

#endif //OS_FILEMANAGER_H

