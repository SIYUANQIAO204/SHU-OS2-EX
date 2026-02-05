//
// Created by qiao on 25-12-7.
//

#ifndef OS_PCBCLOCKCHAIN_H
#define OS_PCBCLOCKCHAIN_H
#include "PCB.h"
#include "PCBchain.h"
#pragma once
namespace pro {
    class PCBclockchain: public PCBchain {
    public:
        PCBclockchain (PCB* he= nullptr, PCB* ta= nullptr)
                : PCBchain(he,ta) {};
        ~PCBclockchain() override {
            PCB* cut=head;
            while(cut!= nullptr)
            {
                PCB* temp = cut->getNextPCB();
                delete cut;
                cut = temp;
            }
        }
        void insertNewPCB(PCB* pcb) override;
        void run() override;
        bool finish() override;

    };
}


#endif //OS_PCBCLOCKCHAIN_H
