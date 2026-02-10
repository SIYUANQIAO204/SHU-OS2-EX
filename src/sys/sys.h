
//
// Created by qiao on 25-12-7.
//定义了整个系统,拥有各个Manager

#ifndef OS_SYS_H
#define OS_SYS_H
#pragma once
#include "../memory/VMmanager.h"
#include "../process/deadlock.h"
#include "../process/PCBchain.h"
#include "../resources/resources.h"
#include "../user/userManager.h"
#include "../file/fileManager.h"
#include <vector>
#include <optional>
#include <memory>
namespace sys {
    class sys : public std::enable_shared_from_this<sys> {
    private:
        int cuttime;//系统当前时间
        //这两个应该写成系统常数
        int memorysize;
        int Blocksize;
        //各个管理器
        std::unique_ptr<memory::VMmanager> memoryManager;
        std::vector<std::unique_ptr<pro::PCBchain>> ProcessManager;
        std::vector<resource::resources> ResourcesManager;
        resource::resourcesmanager DeadlockManager;
        user::userManager UserManager;
        std::shared_ptr<file::fileManager> FileManager;
        std::shared_ptr<file::fileSystem> file_system;
        //管理员
        std::shared_ptr<user::user> Administer;
    public:
        sys(int cut = 0, int memorize = 1024*64, int blocksize = 1024, std::vector<resource::resources> res = {} )
                : cuttime(cut), memorysize(memorize), Blocksize(blocksize), ResourcesManager(res), DeadlockManager(res),UserManager() {
            memoryManager = std::make_unique<memory::VMmanager>(memorize,Blocksize);
            UserManager.createUser("Administer", "123456", user::UserClass::Administer);
            UserManager.createUser("Guest", "", user::UserClass::Guest);
            Administer = UserManager.getUser(0);
            file_system = std::make_shared<file::fileSystem>();
            FileManager = std::make_shared<file::fileManager>();
        }

        ~sys() = default;

        void foo() {
            std::shared_ptr<sys> self = shared_from_this();
            bar(self);
        }

        void bar(std::shared_ptr<sys> p) {}
        void init();
        int getCutTime() const { return cuttime; }
        inline void passtime() {cuttime++;}
        int getBlocknum() const { return memorysize / Blocksize; }
        void creatProcess(int pid, int prio, int memory, int time_needed, int Blocknum, Memory_Sat strategy,
                          std::vector<int> max_needed, int user=0, int CPU = 0);
        void allocateResource(std::vector<int> res, int CPU = 0);
        int visitVM(int VMid, int CPU = 0, int VMaddress = 0);
        void run(int CPU=0);
        void finish(int CPU = 0);
        void addResource(int size);
        std::vector<std::vector<int>> getAllocation() const {return DeadlockManager.getAllocation();}
        std::vector<std::vector<int>> getMaxNeed() const {return DeadlockManager.getMaxNeed();}
        //void
        //createForkProccess(int pid, int prio, int memory, int Blocknum, int time_needed, std::vector<int> max_needed);
        void addProceeManager(PCB_Sta strategy);
        int choosePCBchainWithMaxProcess();
        bool PCBchainEmpty(int CPU=0) {return ProcessManager[CPU]->empty();}
        int getHeadBlockNum(int CPU = 0);
        int getHeadPid(int CPU = 0) {
            if (CPU < 0 || CPU >= (int)ProcessManager.size()) return -1;
            if (!ProcessManager[CPU]) return -1;
            return ProcessManager[CPU]->getHeadPID();
        }
        std::vector<int> getAvailable() const {return DeadlockManager.getAvailable();}
        inline bool allocationEmpty() {return DeadlockManager.allocationEmpty();}
        inline std::vector<int> getDeadLockProcess() const {return DeadlockManager.getIndexToProcess();}
        bool maxNeedCheck(int CPU);
        bool checkAndFinish(int CPU);
        int getPIDChainNum() const {return ProcessManager.size();}
        std::optional<std::pair<int, int>> getProcessBlockNumAndVMnum (int CPU) const;
        void createUser(std::string name, std::string passwd, user::UserClass premission, int group);
        bool login(int uid, std::string passwd);
        int getUserIdbyName(std::string name);
        void deleteUser(int uid);
        void ShowAllUserInfo() const;
        void showUserInfo(int uid) const;
        void setUserGroup(int uid,int gid);
        bool checkPremission(int uid, file::Permission premission) const;
        std::shared_ptr<file::fdtable> getFDTable(int uid);
        void logout(int uid);
        int getNewFileID() {return file_system->allocateNewFileID();}
        std::shared_ptr<user::user> getUserByUID(int uid) {return UserManager.getUserByUid(uid);}
    };

}
#endif //OS_SYS_H

