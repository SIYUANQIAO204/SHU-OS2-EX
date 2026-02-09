
//
// Created by qiao on 25-12-7.
//
/*本文件定义了PCB链的基类，一个链对应一个CPU的进程就绪队列
 *可以为链定义各自的进程调度策略
 *只定义了一些基础的信息管理函数
 */

#include "PCB.h"
#ifndef OS_PCBCHAIN_H
#define OS_PCBCHAIN_H
#pragma once

enum class PCB_Sta{
    clock,
    prio
};


namespace pro{
    class PCBchain{
    protected:
        PCB* head;
        PCB* tail;
        bool running;
        bool alive;
    public:
        PCBchain(PCB* hea= nullptr,PCB* tai = nullptr)
        :head(hea), tail(tai) {running = false;alive = false;};
        virtual ~PCBchain() = default;
        virtual void insertNewPCB(PCB* pcb) {};
        virtual void run() {};
        PCB* getProcess(int pid);
        virtual bool finish() = 0;
        inline int getHeadPID() const {return head->getPID();}
        inline PCB* getHeadProcess() const {return head;}
        int getProcessNum() const;
        bool empty() {return head == nullptr;}
        bool isAlive() const {return alive;}
        bool headPCBMeetMaxNeed() const;
        void showinfo();
        int getHeadProcessUID()const {return head->getUID();}
        void setHeadProcessUID(int user) const { head->setUID(user); }
    };
}



#endif //OS_PCBCHAIN_H
