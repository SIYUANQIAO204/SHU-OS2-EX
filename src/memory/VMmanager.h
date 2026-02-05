//
// Created by qiao on 25-12-8.
//

#ifndef OS_VMMANAGER_H
#define OS_VMMANAGER_H
#pragma once

#include <memory>
#include <iostream>
#include "vector"
#include "memory.h"
#include "Blocks.h"
#include "FIFOBlocks.h"
#include "map"
#include "unordered_map"
#include "OPT.h"
namespace memory {
    class VMmanager {
    private:
        int memory_size;
        int VMsize;
        int blockSize;
        int blocknum;
        std::vector<int> pid;
        std::vector<std::unique_ptr<Blocks>> processBlock;
        std::vector<int> available_blocks;
        std::vector<std::vector<VM>> processVM;
        std::unordered_map<int, int> pid2idx;
        std::vector<int> hit_counter;
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
        bool insertFIFOProcess(int process,int Blocknum,int mem)
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
        int visitVM(int process, int VMid, int VMaddress);
        void releaseProcess(int process);
        void writeback(int process, int VMid);
        void modifyVM(int process,int VMid,int VMaddress = 0,int content = 0);
        int getIndexByPid(int pid);
        void resetHitCounter(int process);
        int getHitCounter (int process);
        void shoInfo(int process);
        std::pair<int,int> getProcessBnumAndVMnum(int process);
    };
}

#endif //OS_VMMANAGER_H
