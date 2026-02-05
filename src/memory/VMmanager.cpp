<<<<<<< HEAD
//
// Created by qiao on 25-12-8.
//

#include "VMmanager.h"
#include "LRUBlocks.h"
namespace memory{

    int VMmanager::getIndexByPid(int pid) {
        auto it = pid2idx.find(pid);
        return (it != pid2idx.end()) ? it->second : -1;
    }

    bool VMmanager::insertLRUProcess(int process, int Blocknum, int mem) {
        int VMnum = (mem+blockSize-1)/blockSize;
        if(Blocknum > (int) available_blocks.size())
        {
            std::cout<<"Lack memory, allocation Process fail\n";
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
        int idx = pid.size();          // 新进程位置
        pid.push_back(process);
        pid2idx[process] = idx;

        processBlock.push_back(
                std::make_unique<LRUBlocks>( process, Blocknum, blockid)
        );
        return true;
    }

    void VMmanager::releaseProcess(int process) {
        int p = getIndexByPid(process);
        if(p == -1) return;
        for(auto q:processBlock[p]->getAllBid()){
            available_blocks.push_back(q);
        }
        processBlock.erase(processBlock.begin()+p);
        pid.erase(pid.begin()+p);
        processVM.erase(processVM.begin()+p);
        hit_counter.erase(hit_counter.begin()+p);
        pid2idx.erase(process);
        for (auto &kv : pid2idx) {
            if (kv.second > p) {
                kv.second--;
            }
        }
    }

    int VMmanager::visitVM(int process, int VMid, int VMaddress) {
        int p = getIndexByPid(process);
        if(p == -1) return -1;
        processVM[p][VMid].visit();
        if(processVM[p][VMid].getExistStatus())
        {
            processBlock[p]->visit(VMid);
            std::cout<<"(VM hit)"<<' ';
            hit_counter[p]++;
            return processVM[p][VMid].getBlockId()*blockSize+VMaddress;
        }
        else
        {
            int pos = processBlock[p]->getNextPos();
            if(!processBlock[p]->blockFull()){
                processBlock[p]->insertVM(VMid,pos);
                processVM[p][VMid].setInMemory();
                processVM[p][VMid].setBlockId(processBlock[p]->getBlockID(pos));
                return processBlock[p]->getBlockID(pos)*blockSize+VMaddress;
            }
            else
            {
                int preVMID =processBlock[p]->getVMID(pos);
                if(processVM[p][preVMID].getModifyStatus()) writeback(process,preVMID);
                processVM[p][preVMID].releaseFromMemory();
                processBlock[p]->insertVM(VMid,pos);
                processVM[p][VMid].setBlockId(processBlock[p]->getBlockID(pos));
                processVM[p][VMid].setInMemory();
                return processBlock[p]->getBlockID(pos)*blockSize+VMaddress;
            }
        }
        return -1;
    }

    void VMmanager::writeback(int process,int VMid) {}

    void VMmanager::modifyVM(int process, int VMid, int VMaddress, int content) {
        visitVM(process,VMid,VMaddress);
        int p = getIndexByPid(process);
        if(p == -1) return;
        processVM[p][VMid].modifing();
    }

    int VMmanager::getHitCounter(int process) {
        int p = getIndexByPid(process);
        return hit_counter[p];
    }

    void VMmanager::resetHitCounter(int process) {
        int p = getIndexByPid(process);
        hit_counter[p] = 0;
    }

    void VMmanager::shoInfo(int process) {
        int p = getIndexByPid(process);
        processBlock[p]->printStratrgy();
        std::cout<<"VM number is "<<(int) processVM[p].size()<<" Block number is "<<processBlock[p]->getblocknum()<<'\n';
        std::cout<<"VM in memory: \n";
        for(auto q:processBlock[p]->getVMid())
        {
            std::cout<<q<<' ';
        }
        std::cout<<'\n';
    }

    std::pair<int, int> VMmanager::getProcessBnumAndVMnum(int process) {
        int p = getIndexByPid(process);
        return std::make_pair(processBlock[p]->getblocknum(),(int) processVM[p].size());
    }

=======
//
// Created by qiao on 25-12-8.
//

#include "VMmanager.h"
#include "LRUBlocks.h"
namespace memory{

    int VMmanager::getIndexByPid(int pid) {
        auto it = pid2idx.find(pid);
        return (it != pid2idx.end()) ? it->second : -1;
    }

    bool VMmanager::insertLRUProcess(int process, int Blocknum, int mem) {
        int VMnum = (mem+blockSize-1)/blockSize;
        if(Blocknum > (int) available_blocks.size())
        {
            std::cout<<"Lack memory, allocation Process fail\n";
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
        int idx = pid.size();          // 新进程位置
        pid.push_back(process);
        pid2idx[process] = idx;

        processBlock.push_back(
                std::make_unique<LRUBlocks>( process, Blocknum, blockid)
        );
        return true;
    }

    void VMmanager::releaseProcess(int process) {
        int p = getIndexByPid(process);
        if(p == -1) return;
        for(auto q:processBlock[p]->getAllBid()){
            available_blocks.push_back(q);
        }
        processBlock.erase(processBlock.begin()+p);
        pid.erase(pid.begin()+p);
        processVM.erase(processVM.begin()+p);
        hit_counter.erase(hit_counter.begin()+p);
        pid2idx.erase(process);
        for (auto &kv : pid2idx) {
            if (kv.second > p) {
                kv.second--;
            }
        }
    }

    int VMmanager::visitVM(int process, int VMid, int VMaddress) {
        int p = getIndexByPid(process);
        if(p == -1) return -1;
        processVM[p][VMid].visit();
        if(processVM[p][VMid].getExistStatus())
        {
            processBlock[p]->visit(VMid);
            std::cout<<"(VM hit)"<<' ';
            hit_counter[p]++;
            return processVM[p][VMid].getBlockId()*blockSize+VMaddress;
        }
        else
        {
            int pos = processBlock[p]->getNextPos();
            if(!processBlock[p]->blockFull()){
                processBlock[p]->insertVM(VMid,pos);
                processVM[p][VMid].setInMemory();
                processVM[p][VMid].setBlockId(processBlock[p]->getBlockID(pos));
                return processBlock[p]->getBlockID(pos)*blockSize+VMaddress;
            }
            else
            {
                int preVMID =processBlock[p]->getVMID(pos);
                if(processVM[p][preVMID].getModifyStatus()) writeback(process,preVMID);
                processVM[p][preVMID].releaseFromMemory();
                processBlock[p]->insertVM(VMid,pos);
                processVM[p][VMid].setBlockId(processBlock[p]->getBlockID(pos));
                processVM[p][VMid].setInMemory();
                return processBlock[p]->getBlockID(pos)*blockSize+VMaddress;
            }
        }
        return -1;
    }

    void VMmanager::writeback(int process,int VMid) {}

    void VMmanager::modifyVM(int process, int VMid, int VMaddress, int content) {
        visitVM(process,VMid,VMaddress);
        int p = getIndexByPid(process);
        if(p == -1) return;
        processVM[p][VMid].modifing();
    }

    int VMmanager::getHitCounter(int process) {
        int p = getIndexByPid(process);
        return hit_counter[p];
    }

    void VMmanager::resetHitCounter(int process) {
        int p = getIndexByPid(process);
        hit_counter[p] = 0;
    }

    void VMmanager::shoInfo(int process) {
        int p = getIndexByPid(process);
        processBlock[p]->printStratrgy();
        std::cout<<"VM number is "<<(int) processVM[p].size()<<" Block number is "<<processBlock[p]->getblocknum()<<'\n';
        std::cout<<"VM in memory: \n";
        for(auto q:processBlock[p]->getVMid())
        {
            std::cout<<q<<' ';
        }
        std::cout<<'\n';
    }

    std::pair<int, int> VMmanager::getProcessBnumAndVMnum(int process) {
        int p = getIndexByPid(process);
        return std::make_pair(processBlock[p]->getblocknum(),(int) processVM[p].size());
    }

>>>>>>> 320bfbd07e519d91666d3598d3577053a0f562b8
}