/*本文件定义了进程控制块，包含进程id，父进程id，进程状态等信息
 *函数包括接受释放资源，资源请求合法性检测
 *PCB之间以链表形式链接
 */
#pragma once
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <sstream>
enum class ProcessState {
    NEW,//刚创建
    WAIT,//就绪
    RUNNING,//运行中
    BLOCKED,//阻塞
    FINISHED,//已完成
    TERMINATED//终止
};

namespace pro {
    class PCB {
    private:
        int pid;                        // 进程号
        int ppid;
        ProcessState state;             // 进程状态
        int priority;                   // 优先级
        int programCounter;             // 程序计数器 PC
        std::vector<int> registers;     // 现场寄存器（模拟）
        std::vector<int> max_registers;//最大资源需求
        int uid;//创建该进程的用户id
        int memory;//进程所需内存
        int arrivaltime;//进程进入就绪队列的时间
        PCB* next;//链表上的下一个进程
        int timetoprocess;//所需运行时间
    public:
        PCB(int id, int prio, int TTP, int arrival, int memory, int UID=0, PCB *nextPCB = NULL, int parent = 0)
                : pid(id), priority(prio), ppid(parent), arrivaltime(arrival), memory(memory), uid(UID), timetoprocess(TTP), next(nextPCB), state(ProcessState::NEW), programCounter(0), registers(8, 0),max_registers(8,0) {};

        ~PCB() = default;
        // ------------ 基本信息管理 ------------
        int getPID() const { return pid; }

        int getPriority() const { return priority; }

        int getPPID() const { return ppid; }

        PCB* getNextPCB() const {return next;}

        int gettimetoprocess() const {return timetoprocess;}

        ProcessState getState() const { return state; }

        int getPC() const { return programCounter; }

        void setPriority(int p) { priority = p; }

        int getArrivalTime(int t) { return arrivaltime;}

        void setState(ProcessState newState) {
            state = newState;
        }

        void setMaxRegister(std::vector<int> max_resources_reuqired)
        {
            max_registers=std::move(max_resources_reuqired);
            return;
        }

        void setRegister(std::vector<int> resources_get)
        {
            registers = std::move(resources_get);
            return;
        }

        std::vector<int> getMaxRegister() const
        {
            return max_registers;
        }

        std::vector<int> getAllocatedResources () const
        {
            return registers;
        }

        bool legalRequire(std::vector<int> require)
        {
            if(require.size()!=registers.size()) return false;
            for(int i=0;i<(int) require.size();i++)
            {
                if(require[i]>max_registers[i]) return false;
            }
            return true;
        }

        int getMemory() const { return memory;}

        void setUID(int user) {uid = user;}

        int getUID() const {return uid;}

        void setMemory(int mem) {memory=mem;}

        void getResources(std::vector<int> allocation)
        {
            for(int i = 0; i < (int)registers.size();i++)
            {
                registers[i] +=allocation[i];
            }
        }
        //设置链上的下一个PCB
        void setnexPCB(PCB* nextPCB) {next = nextPCB;}

        // ------------ 模拟进程执行 ------------
        void executeOneStep() {
            if (state == ProcessState::RUNNING) {
                programCounter++;
            }
        }

        bool finishCheck() const
        {
            return programCounter >= timetoprocess;
        }

        // ------------ 保存上下文（模拟） ------------
        void saveContext(const std::vector<int> &ctx, int pc) {
            registers = ctx;
            programCounter = pc;
        }

        // ------------ 恢复上下文（模拟） ------------
        void loadContext(std::vector<int> &ctx_out, int &pc_out) const {
            ctx_out = registers;
            pc_out = programCounter;
        }

        // ------------ 信息输出 ------------
        std::string toString() const {
            std::stringstream ss;
            ss << "PID=" << pid << " PPID=" << ppid
               << "  State=" << stateToString(state)
               << "  Priority=" << priority
               << "  PC=" << programCounter;
            return ss.str();
        }
        // 检验最大需求的满足
        bool meetMaxNeed() const{
            for(int i = 0;i<(int)registers.size();i++)
            {
                if(registers[i]<max_registers[i]) return false;
            }
            return true;
        }

    private:
        static std::string stateToString(ProcessState s) {
            switch (s) {
                case ProcessState::NEW:
                    return "NEW";
                case ProcessState::WAIT:
                    return "WAIT";
                case ProcessState::RUNNING:
                    return "RUNNING";
                case ProcessState::BLOCKED:
                    return "BLOCKED";
                case ProcessState::TERMINATED:
                    return "TERMINATED";
                case ProcessState::FINISHED:
                    return "FINISHED";
            }
            return "UNKNOWN";
        }
    };
}

