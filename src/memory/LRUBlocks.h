//
// Created by qiao on 25-12-9.
//

#ifndef OS_LRUBLOCKS_H
#define OS_LRUBLOCKS_H
#pragma once
#include "Blocks.h"

#include <utility>
namespace memory{
    class LRUBlocks: public Blocks{
    private:
        std::vector<int> vis;
    public:
        LRUBlocks(int process,int num, std::vector<int> block, std::vector<int> VN = {}, int VNnum=0, int point = 0, std::vector<int> vistime={})
                : Blocks(process,num, std::move(block), std::move(VN),  VNnum, point) {
            vis = vistime;
            VM_id.resize(block_num, -1);
            vis.resize(block_num, 0);
            sat = Memory_Sat::LRU;
        }
        ~LRUBlocks() = default;
        int getNextPos() override {
            if (VMnum < block_num) {
                return VMnum;
            }

            int lru = 0;
            for (int i = 1; i < block_num; i++) {
                if (vis[i] > vis[lru]) {
                    lru = i;
                }
            }
            return lru;
        }

        void insertVM(int VMid, int pos) override {
            if (VMnum < block_num) {
                VM_id[VMnum] = VMid;
                vis[VMnum] = 0;
                VMnum++;
            } else {
                VM_id[pos] = VMid;
                vis[pos] = 0;
            }
        }


        void visit(int VMid) override {
            for (int i = 0; i < VMnum; i++) {
                if (VM_id[i] == VMid) vis[i] = 0;
                else vis[i]++;
            }
        }

        void printStratrgy() const override{
            std::cout<<"Memory strategy is LRU\n";
        }

    };
}
#endif //OS_LRUBLOCKS_H
