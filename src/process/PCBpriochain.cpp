<<<<<<< HEAD
//
// Created by qiao on 25-12-5.
//
#include "PCBpriochain.h"
#include <iostream>
namespace pro{
    void PCBpriochain::insertNewPCB(PCB* pcb) {
        if (!pcb) return;

        // ★ 核心：强制断链，防止带着旧 next
        pcb->setnexPCB(nullptr);

        // 空链表
        if (head == nullptr) {
            head = tail = pcb;
            alive = true;
            return;
        }

        // 头插
        if (pcb->getPriority() > head->getPriority()) {
            pcb->setnexPCB(head);
            head = pcb;
            return;
        }

        // 查找插入点
        PCB* cur = head;
        while (cur->getNextPCB() != nullptr &&
               cur->getNextPCB()->getPriority() >= pcb->getPriority()) {
            cur = cur->getNextPCB();
        }

        // 插入到 cur 后
        pcb->setnexPCB(cur->getNextPCB());
        cur->setnexPCB(pcb);

        // ★ 如果插在最后，更新 tail
        if (pcb->getNextPCB() == nullptr) {
            tail = pcb;
        }
    }

    void PCBpriochain::run() {
        if(!alive||head == nullptr)
        {
            std::cout<<"No pro ready"<<'\n';
            return;
        }
        head->setState(ProcessState::RUNNING);
        head->executeOneStep();
        running = true;
    }

    bool PCBpriochain::finish() {
        if (!alive||!running || head == nullptr) {
            std::cout << "no process running\n";
            return false;
        }

        PCB* cut = head;
        head = head->getNextPCB();

        if (cut == tail) {
            tail = nullptr;
        }

        cut->setnexPCB(nullptr); // ★ 断链

        if (cut->finishCheck()) {
            cut->setState(ProcessState::FINISHED);
            delete cut;
            running = false;
            if (head == nullptr) {
                tail = nullptr;
                alive = false;
            }
            return true;
        }

        // 未完成
        cut->setState(ProcessState::WAIT);
        if (cut->getPriority() > 0)
            cut->setPriority(cut->getPriority() - 1);

        insertNewPCB(cut);   // 重新插入
        running = false;
        return false;
    }

}
=======
//
// Created by qiao on 25-12-5.
//
#include "PCBpriochain.h"
#include <iostream>
namespace pro{
    void PCBpriochain::insertNewPCB(PCB* pcb) {
        if (!pcb) return;

        // ★ 核心：强制断链，防止带着旧 next
        pcb->setnexPCB(nullptr);

        // 空链表
        if (head == nullptr) {
            head = tail = pcb;
            alive = true;
            return;
        }

        // 头插
        if (pcb->getPriority() > head->getPriority()) {
            pcb->setnexPCB(head);
            head = pcb;
            return;
        }

        // 查找插入点
        PCB* cur = head;
        while (cur->getNextPCB() != nullptr &&
               cur->getNextPCB()->getPriority() >= pcb->getPriority()) {
            cur = cur->getNextPCB();
        }

        // 插入到 cur 后
        pcb->setnexPCB(cur->getNextPCB());
        cur->setnexPCB(pcb);

        // ★ 如果插在最后，更新 tail
        if (pcb->getNextPCB() == nullptr) {
            tail = pcb;
        }
    }

    void PCBpriochain::run() {
        if(!alive||head == nullptr)
        {
            std::cout<<"No pro ready"<<'\n';
            return;
        }
        head->setState(ProcessState::RUNNING);
        head->executeOneStep();
        running = true;
    }

    bool PCBpriochain::finish() {
        if (!alive||!running || head == nullptr) {
            std::cout << "no process running\n";
            return false;
        }

        PCB* cut = head;
        head = head->getNextPCB();

        if (cut == tail) {
            tail = nullptr;
        }

        cut->setnexPCB(nullptr); // ★ 断链

        if (cut->finishCheck()) {
            cut->setState(ProcessState::FINISHED);
            delete cut;
            running = false;
            if (head == nullptr) {
                tail = nullptr;
                alive = false;
            }
            return true;
        }

        // 未完成
        cut->setState(ProcessState::WAIT);
        if (cut->getPriority() > 0)
            cut->setPriority(cut->getPriority() - 1);

        insertNewPCB(cut);   // 重新插入
        running = false;
        return false;
    }

}
>>>>>>> 320bfbd07e519d91666d3598d3577053a0f562b8
