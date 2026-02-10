
//
// Created by qiao on 25-12-27.
//用于管理文件块的管理器

#ifndef OS_FBLOCKMANAGER_H
#define OS_FBLOCKMANAGER_H
#include "fsconst.h"
#include <vector>
#include <optional>
#pragma once
namespace file {
    //文件块的结构
    struct fBlock{
        int file_data[PTRS_PER_BLOCK];
    };



    class fBlockManager {
    private:
        fBlock file_block[sysfBlockNum];//系统中所有的文件块
        std::vector<int> available_fbock;//系统中可分配的文件块
    public:
        fBlockManager()  {
                for (int i=0 ; i <  sysfBlockNum ; i++) available_fbock.push_back(i);
        };
        ~fBlockManager() = default;
        void write(int idx,int beg,int ed, std::vector<int> data,int data_beg);//向某一个文件块中写一定长度的数据
        void write(int idx, int pos, int data);//写一个数据
        std::optional<std::vector<int>> read(int idx, int beg, int ed);//读从beg到ed的数据
        void deleteData(int idx,int beg, int ed);//删除beg到ed 的数据
        int read(int idx,int pos);//读pos处的数据
        std::optional<std::vector<int>> allocateBlock (int num);//分配num个文件块
        void getAvailableBlock(std::vector<int> block_release);//回收文件块
    };
}

#endif //OS_FBLOCKMANAGER_H

