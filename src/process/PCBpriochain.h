//
// Created by qiao on 25-12-5.
//

#ifndef OS_PCBPRIOCHAIN_H
#define OS_PCBPRIOCHAIN_H
#include "PCB.h"
#include "PCBchain.h"
#pragma once
namespace pro {
    class PCBpriochain: public PCBchain {
    public:
        PCBpriochain (PCB* he= nullptr, PCB* ta= nullptr)
        : PCBchain(he,ta) {}
        ~PCBpriochain() override {
            PCB* cut=head;
            while(cut!= nullptr)
            {
                PCB* temp = cut->getNextPCB();
                delete cut;
                cut=temp;
            }
        }
        void insertNewPCB(PCB* pcb) override;
        void run() override;
        bool finish() override;
    };
}


#endif //OS_PCBPRIOCHAIN_H
