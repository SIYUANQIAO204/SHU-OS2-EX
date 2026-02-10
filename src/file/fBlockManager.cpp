
//
// Created by qiao on 25-12-27.
//

#include "fBlockManager.h"
namespace file{
    std::optional<std::vector<int>> fBlockManager::read(int idx, int beg, int ed) {
        if( idx >= sysfBlockNum || ed >= PTRS_PER_BLOCK) return std::nullopt;
        std::vector<int> ans;
        for(int i = beg; i <= ed ;i++)
        {
            ans.push_back(file_block[idx].file_data[i]);

        }
        return ans;
    }

    void fBlockManager::write(int idx, int beg, int ed, std::vector<int> data, int data_beg) {
        //beg和ed表示文件块的开始和结束位置，data_beg是要写入这个数据块的数据部分的起始位置
        //这样便于大于文件块大小的数据进行输入
        if( idx >= sysfBlockNum || ed >= PTRS_PER_BLOCK) return;
        for(int i = 0; i <= ed-beg ;i++)
        {
            file_block[idx].file_data[i] = data[data_beg+i];
        }
    }

    void fBlockManager::write(int idx, int pos, int data) {
        if( idx >= sysfBlockNum || pos >= PTRS_PER_BLOCK) return;
        file_block[idx].file_data[pos] = data;
    }

    std::optional<std::vector<int>> fBlockManager::allocateBlock(int num) {
        if((int) available_fbock.size() < num) return std::nullopt;
        else{
            std::vector<int> ans;
            for(int i = 0;i < num;i++)
            {
                ans.push_back( available_fbock.front() );
                available_fbock.erase(available_fbock.begin());
            }
            return ans;
        }
    }

    int fBlockManager::read(int idx, int pos) {
        if( idx >= sysfBlockNum || pos >= PTRS_PER_BLOCK) return -1;
        return file_block[idx].file_data[pos];
    }

    void fBlockManager::deleteData(int idx, int beg, int ed) {
        if( idx >= sysfBlockNum || ed >= PTRS_PER_BLOCK) return;
        for(int i = beg; i < ed; i++)
        {
            file_block[idx].file_data[i] = -1;
        }
    }

    void fBlockManager::getAvailableBlock(std::vector<int> block_release) {
        available_fbock.reserve(available_fbock.size()+block_release.size());
        available_fbock.insert(available_fbock.end(),std::make_move_iterator(block_release.begin()),std::make_move_iterator(block_release.end()));
    }



}