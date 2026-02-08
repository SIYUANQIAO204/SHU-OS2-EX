
//
// Created by qiao on 25-12-11.
//
/*
 * 用于生成随机状态的进程.生成函数需要给定pid以及其余各个参数的最大值
 * */
#ifndef OS_PROCESSGENERATER_H
#define OS_PROCESSGENERATER_H
#pragma once
#include "../sys/sys.h"
#include <random>
#include <vector>
namespace VP {

    struct ProcessParams {
        int pid;                    // 进程号
        int prio;                   // 优先级
        int memory;                 // 占用内存大小
        int time_needed;            // 需要运行时间
        int Blocknum;               // 分配块数
        Memory_Sat strategy;        // 页面置换策略
        std::vector<int> max_needed;// 最大资源需求量
        int CPU;                    // CPU 就绪队列编号
    };

    class RandomProcessGenerator {
    private:
        std::mt19937 gen;
        int BlockSize;
    public:
        RandomProcessGenerator(int bsize) {
            std::random_device rd;
            gen = std::mt19937(rd());
            BlockSize =bsize;
        }

        int randInt(int maxv) {
            if (maxv <= 0) return 0;
            std::uniform_int_distribution<> dist(0, maxv);
            return dist(gen);
        }

        Memory_Sat randomStrategy() {
            std::uniform_int_distribution<> dist(0, 1);
            return static_cast<Memory_Sat>(dist(gen));
        }

        std::vector<int> randomMaxNeed(int resourceKinds, int maxValPerResource) {
            std::vector<int> v(resourceKinds);
            for (int i = 0; i < resourceKinds; i++)
                v[i] = randInt(maxValPerResource);
            return v;
        }

        // 返回 ProcessParams 而不是直接创建进程
        ProcessParams generateRandomProcessParams(
                int pid,
                int maxPrio,
                int maxMemory,
                int maxTimeNeeded,
                int maxBlocknum,
                int resourceKinds,
                int maxResourcePerKind,
                int cpuQueues
        ) {
            ProcessParams p;
            p.pid = pid;
            p.prio = randInt(maxPrio)+1;
            p.memory = randInt(maxMemory)+1;
            p.time_needed = randInt(maxTimeNeeded)+1;
            p.Blocknum = std::min(randInt(maxBlocknum), p.memory/BlockSize)+1;
            p.strategy = randomStrategy();
            p.max_needed = randomMaxNeed(resourceKinds, maxResourcePerKind);
            p.CPU = randInt(cpuQueues - 1);
            return p;
        }
    };
}

#endif //OS_PROCESSGENERATER_H