//
// Created by qiao on 25-12-7.
//

#include "sys.h"
#include "../process/PCBpriochain.h"
#include "../process/PCBclockchain.h"
#include <utility>
namespace sys{
    int sys::visitVM(int VMid, int CPU, int VMaddress) {
        return memoryManager->visitVM(ProcessManager[CPU]->getHeadPID(), VMid, VMaddress);
    }

    void sys::creatProcess(int pid, int prio, int memory, int time_needed, int Blocknum, Memory_Sat strategy,
                           std::vector<int> max_needed, int user, int CPU) {
        auto* temp = new pro::PCB(pid, prio, time_needed, cuttime, memory, user, nullptr,0);
        temp->setState(ProcessState::WAIT);
        temp->setMaxRegister(std::move(max_needed));
        temp->setRegister(std::vector<int>(4,0));
        ProcessManager[CPU]->insertNewPCB(temp);
        if(strategy == Memory_Sat::FIFO)
        {
            memoryManager->insertFIFOProcess(pid, Blocknum, memory);
        }
        else if(strategy == Memory_Sat::LRU)
        {
            memoryManager->insertLRUProcess(pid,Blocknum,memory);
        }
    }

    void sys::allocateResource(std::vector<int> res, int CPU) {
        if (CPU < 0 || CPU >= (int)ProcessManager.size()) return;
        if (!ProcessManager[CPU]) return;
        std::cout<<"Process "<<ProcessManager[CPU]->getHeadPID()<<" is requiring resources:\n";
        for(auto p:res) std::cout<<p<<" ";
        std::cout<<'\n';
        if(!DeadlockManager.allocateResources(ProcessManager[CPU]->getHeadPID(),res)){
            return;
        }
        else{
            ProcessManager[CPU]->getHeadProcess()->getResources(res);
        }
    }



    void sys::run(int CPU) {
        if (CPU < 0 || CPU >= (int)ProcessManager.size()) return;
        if (!ProcessManager[CPU]) return;
        std::cout<<ProcessManager[CPU]->getHeadProcess()->toString()<<'\n';
        ProcessManager[CPU]->run();
        memoryManager->resetHitCounter(ProcessManager[CPU]->getHeadPID());
        ProcessManager[CPU]->showinfo();
        memoryManager->shoInfo(ProcessManager[CPU]->getHeadPID());
        DeadlockManager.insertProcess(ProcessManager[CPU]->getHeadPID(),ProcessManager[CPU]->getHeadProcess()->getMaxRegister());
    }

    void sys::addResource(int size) {
        ResourcesManager.emplace_back(size);
        DeadlockManager.insertResources(ResourcesManager.back());
    }

    void sys::finish(int CPU) {
        if (CPU < 0 || CPU >= (int)ProcessManager.size()) return;
        if (!ProcessManager[CPU]) return;
        int pid = ProcessManager[CPU]->getHeadPID();
        std::cout<<"Hit num = "<<memoryManager->getHitCounter(pid)<<'\n';
        memoryManager->resetHitCounter(pid);
        DeadlockManager.releaseResources(ProcessManager[CPU]->getHeadPID());
        if(ProcessManager[CPU]->finish())
        {
            memoryManager->releaseProcess(pid);
            return;
        }
        return;
    }

    void sys::addProceeManager(PCB_Sta strategy) {
        if(strategy == PCB_Sta::prio) ProcessManager.emplace_back(std::make_unique<pro::PCBpriochain>());
        else if(strategy == PCB_Sta::clock) ProcessManager.emplace_back(std::make_unique<pro::PCBclockchain>());
    }

    int sys::choosePCBchainWithMaxProcess() {
        int ans = 0;
        for(int i=1;i < (int)ProcessManager.size();i++)
        {
            if(ProcessManager[i]->getProcessNum() > ProcessManager[ans]->getProcessNum()){
                ans = i;
            }
        }
        return ans;
    }

    int sys::getHeadBlockNum(int CPU) {
        if(ProcessManager[CPU]->empty()) return 0;
        return ((ProcessManager[CPU]->getHeadProcess()->getMemory()+Blocksize-1)/Blocksize);
    }

    bool sys::maxNeedCheck(int CPU) {
        if (CPU < 0 || CPU >= (int)ProcessManager.size()) return false;
        if (!ProcessManager[CPU]) return false;
        return ProcessManager[CPU]->headPCBMeetMaxNeed();
    }

    bool sys::checkAndFinish(int CPU) {
        if (CPU < 0 || CPU >= (int)ProcessManager.size()) return false;
        if (!ProcessManager[CPU]) return false;
        if(maxNeedCheck(CPU)){
            std::cout<<"Process "<<ProcessManager[CPU]->getHeadPID()<<" finish\n";
            finish(CPU);
            return true;
        }
        return false;
    }

    std::optional<std::pair<int, int>> sys::getProcessBlockNumAndVMnum(int CPU) const {
        if (CPU < 0 || CPU >= (int)ProcessManager.size()) return std::nullopt;
        if (!ProcessManager[CPU]) return std::nullopt;
        return memoryManager->getProcessBnumAndVMnum(ProcessManager[CPU]->getHeadPID());
    }

    void sys::createUser(std::string name, std::string passwd, user::UserClass premission, int group) {
        UserManager.createUser(std::move(name), std::move(passwd), premission, group);
    }

    bool sys::login(int uid, std::string passwd) {
        if(UserManager.loginin(uid, std::move(passwd))){
            FileManager->switchFDTable(uid);
            return true;
        }
        return false;
    }

    int sys::getUserIdbyName(std::string name) {
        return UserManager.getUidByName(name);
    }

    void sys::deleteUser(int uid) {
        FileManager ->deleteFDTable(uid);
        UserManager.deleteUser(uid);
    }

    void sys::ShowAllUserInfo() const {
        UserManager.showAllUserInfo();
    }

    void sys::showUserInfo(int uid) const {
        UserManager.showUserInfo(uid);
    }

    void sys::setUserGroup(int uid, int gid){
        UserManager.setGroup(uid, gid);
    }

    bool sys::checkPremission(int uid, file::Permission premission) const {
        return UserManager.checkPremission(uid, premission, 0);
    }

    void sys::logout(int uid) {
        FileManager->deleteFDTable(uid);
    }

    std::shared_ptr<file::fdtable> sys::getFDTable(int uid) {
        return FileManager->switchFDTable(uid);
    }

    void sys::init() {
        FileManager->createFDTable(getUserByUID(0),file_system);
        FileManager->createFDTable(getUserByUID(1),file_system);
        file_system->setroot();
        FileManager->switchFDTable(0)->openNewFile("home",3);
        FileManager->switchFDTable(1)->openNewFile("home",3);
        FileManager->switchFDTable(0)->createFile(getNewFileID(),file::InodeType::DIRECTORY,"Administer");
        FileManager->switchFDTable(1)->createFile(getNewFileID(),file::InodeType::DIRECTORY,"Guest");
        FileManager->switchFDTable(0)->openFile(getUserByUID(0)->getHomeDir(),3);
        FileManager->switchFDTable(1)->openFile(getUserByUID(1)->getHomeDir(),3);
    }



}