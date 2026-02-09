
//
// Created by qiao on 25-12-8.
//
/*本文件定义的是进程的实际内存块的管理，包括所属进程id等信息
 */

#ifndef OS_BLOCKS_H
#define OS_BLOCKS_H
#pragma once
#include <vector>

enum class Memory_Sat{
    FIFO,
    LRU
};

namespace memory{
    class Blocks{
    protected:
        int pid;//所属进程id
        int VMnum;//进程所需虚拟页的页数
        std::vector<int> block_id;//被分配到的内存块集合
        std::vector<int> VM_id;//当前在内存块中的页号
        int block_num;;//拥有的块的数目
        int pointer;//指向
        Memory_Sat sat;//内存调度策略
    public:
        Blocks(int process,int num, std::vector<int> block, std::vector<int> VN = {}, int VNnum=0, int point = 0)
        : pid(process), block_num(num), block_id(block), VM_id(VN), pointer(point),VMnum(VNnum) {};
        virtual ~Blocks() = default;
        bool blockFull() const {return VMnum >= block_num;};
        virtual int getNextPos() =0;//获取下一个替换的位置，LRU用
        virtual void insertVM(int VMid, int pos) {};//调入虚拟页
        std::vector<int> getAllBid () const {return block_id;}
        int getBlockID(int suffix) const {  return block_id[suffix];}
        int getVMID(int pos) const {return VM_id[pos];}
        virtual void visit(int VMid) {};//访问某个页面
        int getblockIdSize() const {return (int)block_id.size();}
        int getblocknum() const {return block_num;}
        int getVMnum() const {return VMnum;}
        std::vector<int> getVMid () const {return VM_id;}
        virtual void printStratrgy () const {};//输出调度策略
    };
}
#endif //OS_BLOCKS_H

