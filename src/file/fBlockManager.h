<<<<<<< HEAD
//
// Created by qiao on 25-12-27.
//

#ifndef OS_FBLOCKMANAGER_H
#define OS_FBLOCKMANAGER_H
#include "fsconst.h"
#include "vector"
#include "optional"
#pragma once
namespace file {

    struct fBlock{
        int file_data[PTRS_PER_BLOCK];
    };



    class fBlockManager {
    private:
        fBlock file_block[sysfBlockNum];
        std::vector<int> available_fbock;
    public:
        fBlockManager()  {
                for (int i=0 ; i <  sysfBlockNum ; i++) available_fbock.push_back(i);
        };
        ~fBlockManager() = default;
        void write(int idx,int beg,int ed, std::vector<int> data,int data_beg);
        void write(int idx, int pos, int data);
        std::optional<std::vector<int>> read(int idx, int beg, int ed);
        void deleteData(int idx,int beg, int ed);
        int read(int idx,int pos);
        std::optional<std::vector<int>> allocateBlock (int num);
        void getAvailableBlock(std::vector<int> block_release);
    };
}

#endif //OS_FBLOCKMANAGER_H
=======
//
// Created by qiao on 25-12-27.
//

#ifndef OS_FBLOCKMANAGER_H
#define OS_FBLOCKMANAGER_H
#include "fsconst.h"
#include "vector"
#include "optional"
#pragma once
namespace file {

    struct fBlock{
        int file_data[PTRS_PER_BLOCK];
    };



    class fBlockManager {
    private:
        fBlock file_block[sysfBlockNum];
        std::vector<int> available_fbock;
    public:
        fBlockManager()  {
                for (int i=0 ; i <  sysfBlockNum ; i++) available_fbock.push_back(i);
        };
        ~fBlockManager() = default;
        void write(int idx,int beg,int ed, std::vector<int> data,int data_beg);
        void write(int idx, int pos, int data);
        std::optional<std::vector<int>> read(int idx, int beg, int ed);
        void deleteData(int idx,int beg, int ed);
        int read(int idx,int pos);
        std::optional<std::vector<int>> allocateBlock (int num);
        void getAvailableBlock(std::vector<int> block_release);
    };
}

#endif //OS_FBLOCKMANAGER_H
>>>>>>> 320bfbd07e519d91666d3598d3577053a0f562b8
