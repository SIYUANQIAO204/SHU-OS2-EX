//
// Created by qiao on 25-12-8.
//

#ifndef OS_BLOCKS_H
#define OS_BLOCKS_H
#pragma once
#include "vector"

enum class Memory_Sat{
    FIFO,
    LRU
};

namespace memory{
    class Blocks{
    protected:
        int pid;
        int VMnum;
        std::vector<int> block_id;
        std::vector<int> VM_id;
        int block_num;;
        int pointer;
        Memory_Sat sat;
    public:
        Blocks(int process,int num, std::vector<int> block, std::vector<int> VN = {}, int VNnum=0, int point = 0)
        : pid(process), block_num(num), block_id(block), VM_id(VN), pointer(point),VMnum(VNnum) {};
        virtual ~Blocks() = default;
        bool blockFull() const {return VMnum >= block_num;};
        virtual int getNextPos() =0;
        virtual void insertVM(int VMid, int pos) {};
        std::vector<int> getAllBid () const {return block_id;}
        int getBlockID(int suffix) const {  return block_id[suffix];}
        int getVMID(int pos) const {return VM_id[pos];}
        virtual void visit(int VMid) {};
        int getblockIdSize() const {return (int)block_id.size();}
        int getblocknum() const {return block_num;}
        int getVMnum() const {return VMnum;}
        std::vector<int> getVMid () const {return VM_id;}
        virtual void printStratrgy () const {};
    };
}
#endif //OS_BLOCKS_H
