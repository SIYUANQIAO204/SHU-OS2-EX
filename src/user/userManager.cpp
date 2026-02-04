//
// Created by qiao on 25-12-25.
//

#include "userManager.h"

#include <utility>
#include "iostream"
namespace user{

    int userManager::getIndexByUid(int uid) const {
        auto it = uidToIndex.find(uid);
        return (it != uidToIndex.end()) ? it->second : -1;
    }

    void userManager::createUser(std::string name, std::string passwd, UserClass premission, int group) {
        uids.emplace_back(next_uid);
        int idx = userNum;
        uidToIndex[next_uid] = idx;
        users.push_back(std::make_unique<user>(next_uid, name, passwd , premission, "", group));
        next_uid++;
        userNum++;
    }

    void userManager::deleteUser(int uid) {
        int idx = getIndexByUid(uid);
        if(idx == -1){
            std::cout<<"Can't find user\n";
            return;
        }
        uids.erase(uids.begin()+idx);
        users.erase(users.begin()+idx);
        uidToIndex.erase(uid);
        for (auto &kv : uidToIndex) {
            if (kv.second > idx) {
                kv.second--;
            }
        }
        userNum--;
    }

    bool userManager::loginin(int uid, std::string passwd) const {
        int idx = getIndexByUid(uid);
        if(idx == -1) return false;
        return users[idx]->checkPasswd(std::move(passwd));
    }

    int userManager::getUidByName(std::string name) const {
        for(int i = 0;i < userNum;i++)
        {
            if(users[i]->checkName(name)) return i;
        }
        return -1;
    }

    void userManager::showAllUserInfo() const {
        for(int i = 0;i < userNum;i++)
        {
            users[i]->showInfo();
        }
    }

    void userManager::showUserInfo(int uid) const {
        int idx = getIndexByUid(uid);
        if(idx == -1) {
            std::cout << "Can't find user\n";
            return;
        }
        users[idx]->showInfo();
    }

    void userManager::setGroup(int uid, int group) {
        int idx = getIndexByUid(uid);
        if(idx == -1) {
            std::cout << "Can't find user\n";
            return;
        }
        users[idx]->setGroup(group);
    }

    void userManager::changeUserPasswd(int uid, std::string newpasswd) {
        int idx = getIndexByUid(uid);
        if(idx == -1) {
            std::cout << "Can't find user\n";
            return;
        }
        users[idx]->changePasswd(newpasswd);
    }

    int userManager::getGroup(int uid) const {
        int idx = getIndexByUid(uid);
        if(idx == -1) {
            std::cout << "Can't find user\n";
            return -1;
        }
        return users[idx]->getGid();
    }

    std::string userManager::getName(int uid) const {
        int idx = getIndexByUid(uid);
        if(idx == -1) {
            std::cout << "Can't find user\n";
            return "";
        }
        return users[idx]->getName();
    }

    void userManager::changePremission(int uid, UserClass premission) {
        int idx = getIndexByUid(uid);
        if(idx == -1) {
            std::cout << "Can't find user\n";
            return ;
        }
        users[idx]->changePremission(premission);
    }

    void userManager::changName(int uid, std::string newName) {
        int idx = getIndexByUid(uid);
        if(idx == -1) {
            std::cout << "Can't find user\n";
            return ;
        }
        users[idx]->changename(newName);
    }

    bool userManager::checkPremission(int uid, file::Permission premission, int owner) const {
        int idx = getIndexByUid(uid);
        if(idx == -1) {
            std::cout << "Can't find user\n";
            return false;
        }
        return users[idx]->checkPremission(premission, owner);
    }

    std::string userManager::getHomeDir(int uid) const {
        int idx = getIndexByUid(uid);
        if(idx == -1) {
            std::cout << "Can't find user\n";
            return "";
        }
        return users[idx]->getHomeDir();
    }

    std::shared_ptr<user> userManager::getUserByUid(int uid) const {
        int idx = getIndexByUid(uid);
        if(idx == -1) return nullptr;
        else return getUser(idx);
    }

}