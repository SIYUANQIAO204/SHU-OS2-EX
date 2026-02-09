
//
// Created by qiao on 25-12-9.
//使用了先入先出策略进行虚存调度

#ifndef OS_FIFOBLOCKS_H
#define OS_FIFOBLOCKS_H
#include "Blocks.h"

#include <utility>
#pragma once
namespace memory {
class FIFOBlocks: public Blocks {
    public:
        FIFOBlocks(int process,int num, std::vector<int> block, std::vector<int> VN = {}, int VNnum=0, int point = 0)
        : Blocks(process,num, std::move(block), std::move(VN),  VNnum, point) {
            VM_id.resize(block_num, -1);
            sat=Memory_Sat::FIFO;
        }
        ~FIFOBlocks() = default;
        int getNextPos() override{
            if (VMnum < block_num) {
                std::cout<<VMnum;
                return VMnum;
            }
            return pointer;
        }

        void insertVM(int VMid, int pos) override {
            VM_id[pos] = VMid;
            if (VMnum < block_num) {
                VMnum++;
            } else {
                pointer = (pointer + 1) % block_num;
            }
        }

        void printStratrgy() const override{
            std::cout<<"Memory Strategy is FIFO\n";
        }


    };
}

#endif //OS_FIFOBLOCKS_H

