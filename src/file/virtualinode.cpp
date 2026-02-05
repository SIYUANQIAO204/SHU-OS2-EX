<<<<<<< HEAD
//
// Created by qiao on 25-12-25.
//

#include "virtualinode.h"
#include "fileSystem.h"
#include "iostream"
namespace file{

    void virtualinode::appendBlcok(int idx) {
        if(block_num < DIRECT_CNT)
        {
            direct[block_num] = idx;
            block_num++;
        }
        else if(block_num < DIRECT_CNT+PTRS_PER_BLOCK)
        {

            auto sp = file_system.lock();
            if(block_num == DIRECT_CNT) single_indirect = sp->allocateOneBlock();
            if(single_indirect == -1) return;
            sp->write(single_indirect, block_num - DIRECT_CNT, idx);
            block_num++;
        }
        else{
            auto sp  = file_system.lock();
            if(block_num == DIRECT_CNT + PTRS_PER_BLOCK) double_indirect = sp->allocateOneBlock();
            if(double_indirect == -1) return;
            if(cut_double_indirect_idx == 0){
                auto pos = sp->allocateOneBlock();
                if(pos == -1) return;
                sp->write(double_indirect, cut_double_indirect_idx, pos);
            }
            sp->write(sp->read_data(double_indirect,cut_double_indirect_idx),cut_double_indirect_pos,idx);
            block_num++;
            cut_double_indirect_pos++;
            if(cut_double_indirect_pos >= PTRS_PER_BLOCK)
            {
                cut_double_indirect_pos -= PTRS_PER_BLOCK;
                cut_double_indirect_idx++;
            }
        }
    }

    int virtualinode::getBlockPos(int lbn) {
        if(lbn < DIRECT_CNT)
        {
            return direct[lbn];
        }
        else if(lbn < DIRECT_CNT + PTRS_PER_BLOCK)
        {
            auto p = file_system.lock();
            if(p == nullptr) return -1;
            return p->read_data(single_indirect,lbn-DIRECT_CNT);
        }
        else{
            auto p = file_system.lock();
            return
            p->read_data(p->read_data(double_indirect,(lbn-DIRECT_CNT+PTRS_PER_BLOCK)/PTRS_PER_BLOCK),(lbn-DIRECT_CNT+PTRS_PER_BLOCK)%PTRS_PER_BLOCK);
        }
    }

    std::optional<std::vector<int>> virtualinode::read(int pos, int len) {
        if(pos + len > size || len < 0 || writing) return std::nullopt;
        read_count++;
        std::vector<int> ans ={};
        int lbn = pos/PTRS_PER_BLOCK;
        pos %=PTRS_PER_BLOCK;
        for(; len >= PTRS_PER_BLOCK;len -= PTRS_PER_BLOCK)
        {

            auto  sp = file_system.lock();
            auto temp =sp->read_data(getBlockPos(lbn),pos, PTRS_PER_BLOCK-1);
            ans.reserve(ans.size()+temp->size());
            ans.insert(ans.end(), std::make_move_iterator(temp->begin()),std::make_move_iterator(temp->end()));
            pos = 0;
            lbn++;
        }
        if(len == 0) {
            read_count--;
            return ans;
        }
        auto sp = file_system.lock();
        auto temp =sp->read_data(lbn,pos, len - 1);
        ans.reserve(ans.size()+temp->size());
        ans.insert(ans.end(), std::make_move_iterator(temp->begin()),std::make_move_iterator(temp->end()));
        read_count--;
        return ans;
    }

    int virtualinode::allocateBlock(int num) {
        if(num+block_num < 0 || num+block_num > DIRECT_CNT + PTRS_PER_BLOCK*(PTRS_PER_BLOCK+1)) return -1;
        auto sp = file_system.lock();
        auto getBlock = sp->allocateBlock(num);
        if(getBlock  == std::nullopt) return -2;
        for(auto p:*getBlock)
        {
            appendBlcok(p);
        }
        return 1;
    }

    int virtualinode::write(int pos, std::vector<int> buf, int len) {
        writing = true;
        if(pos + len > size)
        {
            int new_size = pos + len;
            int st=allocateBlock((new_size + PTRS_PER_BLOCK -1) / PTRS_PER_BLOCK - block_num);
            if(st != 1) return st;
             size = new_size;
        }
        int lbn = pos / PTRS_PER_BLOCK;
        pos %= PTRS_PER_BLOCK;
        int data_pos = 0;
        auto sp = file_system.lock();
        for(;len  > PTRS_PER_BLOCK; len -= PTRS_PER_BLOCK)
        {
            sp->write(getBlockPos(lbn), pos, PTRS_PER_BLOCK-1, buf, data_pos);
            data_pos += PTRS_PER_BLOCK;
            pos = 0;
            lbn++;
        }
        if(len == 0)
        {
            writing = false;
        }
        sp->write(getBlockPos(lbn),pos,len-1,buf,data_pos);
        writing  = false;
        return 1;
    }

    int virtualinode::deleteData(int pos, int len) {
        if(pos + len > size || pos < 0) return -1;
        auto sp = file_system.lock();
        int lbn = pos / PTRS_PER_BLOCK;
        if(pos + len == size)
        {
            pos %= PTRS_PER_BLOCK;
            for(;len > PTRS_PER_BLOCK; len -= PTRS_PER_BLOCK)
            {
                sp->delete_block_data(getBlockPos(lbn), pos, PTRS_PER_BLOCK-1);
                pos = 0;
                lbn++;
            }
        }
        else
        {
            auto temp_buf = read(pos+len, size - pos -len);
            if(temp_buf == std::nullopt) return -1;
            write(pos + len, *temp_buf, sizeof(temp_buf));
            pos = size - pos - len;
            lbn = pos / PTRS_PER_BLOCK;
            pos %= PTRS_PER_BLOCK;
            for(;len > PTRS_PER_BLOCK; len -= PTRS_PER_BLOCK)
            {
                sp->delete_block_data(getBlockPos(lbn), pos, PTRS_PER_BLOCK-1);
                pos = 0;
                lbn++;
            }
            sp->delete_block_data(getBlockPos(lbn), pos, len-1);
        }
        size -= pos + len;
        return 1;
    }

    std::vector<int> virtualinode::release(){
        auto sp = file_system.lock();
        int lbn = 0;
        std::vector<int> ans;
        while(getBlockPos(lbn) !=-1)
        {
            if(sp->read_data(getBlockPos(lbn),0) == -1) ans.push_back((getBlockPos(lbn)));
        }
        return ans;
    }

    std::optional<std::vector<int>> virtualinode::deleteInode(std::string delete_name) {
        if(ref_count > 1 || name != delete_name) return std::nullopt;
        deleteData(0,size);
        auto sp = file_system.lock();
        sp->deleteINode(inode_id);
        return release();
    }

    void virtualinode::showInfo() {
        auto buf = read(0,size);
        for(auto p : *buf){
            std::cout<<p<<' ';
        }
        std::cout<<'\n';
        return;
    }

=======
//
// Created by qiao on 25-12-25.
//

#include "virtualinode.h"
#include "fileSystem.h"
#include "iostream"
namespace file{

    void virtualinode::appendBlcok(int idx) {
        if(block_num < DIRECT_CNT)
        {
            direct[block_num] = idx;
            block_num++;
        }
        else if(block_num < DIRECT_CNT+PTRS_PER_BLOCK)
        {

            auto sp = file_system.lock();
            if(block_num == DIRECT_CNT) single_indirect = sp->allocateOneBlock();
            if(single_indirect == -1) return;
            sp->write(single_indirect, block_num - DIRECT_CNT, idx);
            block_num++;
        }
        else{
            auto sp  = file_system.lock();
            if(block_num == DIRECT_CNT + PTRS_PER_BLOCK) double_indirect = sp->allocateOneBlock();
            if(double_indirect == -1) return;
            if(cut_double_indirect_idx == 0){
                auto pos = sp->allocateOneBlock();
                if(pos == -1) return;
                sp->write(double_indirect, cut_double_indirect_idx, pos);
            }
            sp->write(sp->read_data(double_indirect,cut_double_indirect_idx),cut_double_indirect_pos,idx);
            block_num++;
            cut_double_indirect_pos++;
            if(cut_double_indirect_pos >= PTRS_PER_BLOCK)
            {
                cut_double_indirect_pos -= PTRS_PER_BLOCK;
                cut_double_indirect_idx++;
            }
        }
    }

    int virtualinode::getBlockPos(int lbn) {
        if(lbn < DIRECT_CNT)
        {
            return direct[lbn];
        }
        else if(lbn < DIRECT_CNT + PTRS_PER_BLOCK)
        {
            auto p = file_system.lock();
            if(p == nullptr) return -1;
            return p->read_data(single_indirect,lbn-DIRECT_CNT);
        }
        else{
            auto p = file_system.lock();
            return
            p->read_data(p->read_data(double_indirect,(lbn-DIRECT_CNT+PTRS_PER_BLOCK)/PTRS_PER_BLOCK),(lbn-DIRECT_CNT+PTRS_PER_BLOCK)%PTRS_PER_BLOCK);
        }
    }

    std::optional<std::vector<int>> virtualinode::read(int pos, int len) {
        if(pos + len > size || len < 0 || writing) return std::nullopt;
        read_count++;
        std::vector<int> ans ={};
        int lbn = pos/PTRS_PER_BLOCK;
        pos %=PTRS_PER_BLOCK;
        for(; len >= PTRS_PER_BLOCK;len -= PTRS_PER_BLOCK)
        {

            auto  sp = file_system.lock();
            auto temp =sp->read_data(getBlockPos(lbn),pos, PTRS_PER_BLOCK-1);
            ans.reserve(ans.size()+temp->size());
            ans.insert(ans.end(), std::make_move_iterator(temp->begin()),std::make_move_iterator(temp->end()));
            pos = 0;
            lbn++;
        }
        if(len == 0) {
            read_count--;
            return ans;
        }
        auto sp = file_system.lock();
        auto temp =sp->read_data(lbn,pos, len - 1);
        ans.reserve(ans.size()+temp->size());
        ans.insert(ans.end(), std::make_move_iterator(temp->begin()),std::make_move_iterator(temp->end()));
        read_count--;
        return ans;
    }

    int virtualinode::allocateBlock(int num) {
        if(num+block_num < 0 || num+block_num > DIRECT_CNT + PTRS_PER_BLOCK*(PTRS_PER_BLOCK+1)) return -1;
        auto sp = file_system.lock();
        auto getBlock = sp->allocateBlock(num);
        if(getBlock  == std::nullopt) return -2;
        for(auto p:*getBlock)
        {
            appendBlcok(p);
        }
        return 1;
    }

    int virtualinode::write(int pos, std::vector<int> buf, int len) {
        writing = true;
        if(pos + len > size)
        {
            int new_size = pos + len;
            int st=allocateBlock((new_size + PTRS_PER_BLOCK -1) / PTRS_PER_BLOCK - block_num);
            if(st != 1) return st;
             size = new_size;
        }
        int lbn = pos / PTRS_PER_BLOCK;
        pos %= PTRS_PER_BLOCK;
        int data_pos = 0;
        auto sp = file_system.lock();
        for(;len  > PTRS_PER_BLOCK; len -= PTRS_PER_BLOCK)
        {
            sp->write(getBlockPos(lbn), pos, PTRS_PER_BLOCK-1, buf, data_pos);
            data_pos += PTRS_PER_BLOCK;
            pos = 0;
            lbn++;
        }
        if(len == 0)
        {
            writing = false;
        }
        sp->write(getBlockPos(lbn),pos,len-1,buf,data_pos);
        writing  = false;
        return 1;
    }

    int virtualinode::deleteData(int pos, int len) {
        if(pos + len > size || pos < 0) return -1;
        auto sp = file_system.lock();
        int lbn = pos / PTRS_PER_BLOCK;
        if(pos + len == size)
        {
            pos %= PTRS_PER_BLOCK;
            for(;len > PTRS_PER_BLOCK; len -= PTRS_PER_BLOCK)
            {
                sp->delete_block_data(getBlockPos(lbn), pos, PTRS_PER_BLOCK-1);
                pos = 0;
                lbn++;
            }
        }
        else
        {
            auto temp_buf = read(pos+len, size - pos -len);
            if(temp_buf == std::nullopt) return -1;
            write(pos + len, *temp_buf, sizeof(temp_buf));
            pos = size - pos - len;
            lbn = pos / PTRS_PER_BLOCK;
            pos %= PTRS_PER_BLOCK;
            for(;len > PTRS_PER_BLOCK; len -= PTRS_PER_BLOCK)
            {
                sp->delete_block_data(getBlockPos(lbn), pos, PTRS_PER_BLOCK-1);
                pos = 0;
                lbn++;
            }
            sp->delete_block_data(getBlockPos(lbn), pos, len-1);
        }
        size -= pos + len;
        return 1;
    }

    std::vector<int> virtualinode::release(){
        auto sp = file_system.lock();
        int lbn = 0;
        std::vector<int> ans;
        while(getBlockPos(lbn) !=-1)
        {
            if(sp->read_data(getBlockPos(lbn),0) == -1) ans.push_back((getBlockPos(lbn)));
        }
        return ans;
    }

    std::optional<std::vector<int>> virtualinode::deleteInode(std::string delete_name) {
        if(ref_count > 1 || name != delete_name) return std::nullopt;
        deleteData(0,size);
        auto sp = file_system.lock();
        sp->deleteINode(inode_id);
        return release();
    }

    void virtualinode::showInfo() {
        auto buf = read(0,size);
        for(auto p : *buf){
            std::cout<<p<<' ';
        }
        std::cout<<'\n';
        return;
    }

>>>>>>> 320bfbd07e519d91666d3598d3577053a0f562b8
}