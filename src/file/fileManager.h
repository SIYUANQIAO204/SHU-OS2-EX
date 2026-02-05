<<<<<<< HEAD
//
// Created by qiao on 25-12-30.
//

#ifndef OS_FILEMANAGER_H
#define OS_FILEMANAGER_H
#include "fdtable.h"
namespace file {
    class fileManager {
    private:
        std::vector<std::shared_ptr<fdtable>> folder;
        std::unordered_map<int,int> uid2idx;
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
=======
//
// Created by qiao on 25-12-30.
//

#ifndef OS_FILEMANAGER_H
#define OS_FILEMANAGER_H
#include "fdtable.h"
namespace file {
    class fileManager {
    private:
        std::vector<std::shared_ptr<fdtable>> folder;
        std::unordered_map<int,int> uid2idx;
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
>>>>>>> 320bfbd07e519d91666d3598d3577053a0f562b8
