//
// Created by qiao on 25-12-25.
//

#ifndef OS_USERMANAGER_H
#define OS_USERMANAGER_H
#pragma once
#include "user.h"
#include "map"
#include "unordered_map"
#include "vector"
#include "memory"
namespace user {
    class userManager {
    private:
        int next_uid;
        std::unordered_map<int, int> uidToIndex;
        std::vector<std::shared_ptr<user>> users;
        std::vector<int> uids;
        int userNum;
    public:
        userManager()
        {
            next_uid = 0;
            uidToIndex = {};
            users.clear();
            userNum =0;
        }
        ~userManager() = default;
        void createUser(std::string name,std::string passwd, UserClass premission,int group = 0);
        void deleteUser(int uid);
        int getIndexByUid(int uid) const;
        bool loginin(int uid, std::string passwd) const;
        int getUidByName(std::string name) const;
        void showAllUserInfo() const;
        void showUserInfo(int uid) const;
        void setGroup(int uid, int group);
        void changeUserPasswd(int uid, std::string newpasswd);
        int getGroup(int uid) const;
        std::string getName(int uid) const;
        void changePremission(int uid,UserClass premission);
        void changName(int uid,std::string newName);
        bool checkPremission(int uid, file::Permission premission, int owner) const;
        std::string getHomeDir(int uid) const;
        std::shared_ptr<user> getUser(int idx) const {return users[idx];}
        std::shared_ptr<user> getUserByUid(int uid) const;
    };
}

#endif //OS_USERMANAGER_H
