//
// Created by qiao on 25-12-7.
//

#include "PCBclockchain.h"
#include "iostream"
namespace pro{
    void PCBclockchain::insertNewPCB(PCB* pcb) {
        if (!pcb) return;

        pcb->setnexPCB(nullptr);

        if (head == nullptr) {
            head = tail = pcb;
            alive = true;
            return;
        }

        tail->setnexPCB(pcb);
        tail = pcb;
    }

    void PCBclockchain::run() {
        if (!alive || head == nullptr) {
            std::cout << "No process ready\n";
            return;
        }

        head->setState(ProcessState::RUNNING);
        head->executeOneStep();
        running = true;
    }

    bool PCBclockchain::finish() {
        if (!running || head == nullptr) {
            std::cout << "no process running\n";
            return false;
        }

        PCB* cut = head;
        head = head->getNextPCB();
        cut->setnexPCB(nullptr);

        // ⭐ 正确维护 tail
        if (cut == tail) {
            tail = head;   // head 要么是 nullptr，要么是新尾
        }

        if (cut->finishCheck()) {
            cut->setState(ProcessState::FINISHED);
            delete cut;

            if (head == nullptr) {
                tail = nullptr;
                alive = false;
            }

            running = false;
            return true;
        }

        // 未完成 → 放回队尾
        cut->setState(ProcessState::WAIT);
        if (head) head->setState(ProcessState::WAIT);

        insertNewPCB(cut);

        running = false;
        return false;
    }
}
