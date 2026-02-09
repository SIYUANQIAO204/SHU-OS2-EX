
//
// Created by qiao on 25-12-8.
//用于管理所有进程内存情况的管理器

#ifndef OS_VMMANAGER_H
#define OS_VMMANAGER_H
#pragma once

#include <memory>
#include <iostream>
#include <vector>
#include "memory.h"
#include "Blocks.h"
#include "FIFOBlocks.h"
#include <map>
#include <unordered_map>
#include "OPT.h"
namespace memory {
    class VMmanager {
    private:
        int memory_size;//系统的内存大小
        int VMsize;//一个虚拟页的内存大小
        int blockSize;//一个内存块的大小
        int blocknum;//内存能划分出的内存块的数量
        std::vector<int> pid;//进程id集合
        std::vector<std::unique_ptr<Blocks>> processBlock;//内存块的集合
        std::vector<int> available_blocks;//当前可分配的块的id
        std::vector<std::vector<VM>> processVM;//各个进程的VM
        std::unordered_map<int, int> pid2idx;//id到下标的映射
        std::vector<int> hit_counter;//每个进程的内存命中次数
    public:
        VMmanager(int memsize, int blockSize, std::vector<int> process = {}, std::vector<std::unique_ptr<Blocks>> block = {} )
        : memory_size(memsize), blockSize(blockSize), pid(process), processBlock(std::move(block)) {
            VMsize = blockSize, blocknum = memsize/blockSize;
            processVM = {};
            for(int i=0;i<blocknum;i++) available_blocks.push_back(i);
            pid2idx={};
            hit_counter = {};
        }
        ~VMmanager() = default;
        void setMemSize(int size) {memory_size=size;}
        void setBlockSize(int size) {VMsize = size;blockSize = size;}
        int getMemSize() const {return memory_size;}
        int getBlockSize() const {return VMsize;}
        int getProcessNum() const {return processVM.size();}
        bool insertFIFOProcess(int process,int Blocknum,int mem)//加入一个FIFO策略的进程
        {
            int VMnum = (mem+blockSize-1)/blockSize;
            if(Blocknum > (int) available_blocks.size())
            {
                std::cout<<"Lack memory, allocation Process fail";
                return false;
            }
            std::vector<int> blockid;
            processVM.emplace_back();
            hit_counter.emplace_back(0);
            for(int i=0;i<VMnum;i++)
            {
                processVM.back().emplace_back(i,VMsize*i);
            }
            for(int i=0;i<Blocknum;i++)
            {
                blockid.push_back(available_blocks[0]);
                available_blocks.erase(available_blocks.begin());
            }
            int idx = pid.size();
            pid.push_back(process);
            pid2idx[process] = idx;
            processBlock.push_back(
                    std::make_unique<FIFOBlocks>( process, Blocknum, blockid)
                            );
            return true;
        }
        bool insertLRUProcess(int process, int Blocknum, int mem);
        int visitVM(int process, int VMid, int VMaddress);//访问虚拟页
        void releaseProcess(int process);//释放进程
        void writeback(int process, int VMid);//模拟写会外存
        void modifyVM(int process,int VMid,int VMaddress = 0,int content = 0);
        int getIndexByPid(int pid);//将id转换成下标
        void resetHitCounter(int process);
        int getHitCounter (int process);
        void shoInfo(int process);
        std::pair<int,int> getProcessBnumAndVMnum(int process);
    };
}

#endif //OS_VMMANAGER_H

