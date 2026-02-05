//
// Created by qiao on 25-12-11.
//
#include "PCBchain.h"
namespace pro{
    PCB *PCBchain::getProcess(int pid) {
        PCB* p=head;
        for(;p!= nullptr;p=p->getNextPCB())
        {
            if(p->getPID() == pid) return p;
        }
            std::cout<<"Process not found"<<'\n';
            return nullptr;
    }

    int PCBchain::getProcessNum() const {
        if(head == nullptr) return 0;
        int cnt = 1;auto cut = head;
        for(;cut!= nullptr;cut = cut->getNextPCB())
        {
            cnt++;
        }
        return cnt;
    }

    void PCBchain::showinfo() {
        if(head == nullptr) return;
        std::cout<<"Running Process: "<<getHeadPID()<<'\n';
        std::cout<<"Waiting Process: ";
        auto cut =head->getNextPCB();
        for(;cut!= nullptr;cut= cut->getNextPCB())
        {
            std::cout<<cut->getPID()<<' ';
        }
        std::cout<<'\n';
    }

    bool PCBchain::headPCBMeetMaxNeed() const {
        if(head == nullptr||!alive) return false;
        return head->meetMaxNeed();
    }

}