
//
// Created by qiao on 25-12-28.
//设定了一些系统的常数

#ifndef OS_FSCONST_H
#define OS_FSCONST_H
#pragma once
namespace file{
    constexpr int DIRECT_CNT = 8;//一个文件块
    constexpr int PTRS_PER_BLOCK = 2;//一个文件块中能容纳多少数据
    constexpr int sysfBlockNum = 1024;//系统中有多少文件块
}
#endif //OS_FSCONST_H
