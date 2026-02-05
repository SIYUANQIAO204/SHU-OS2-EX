#pragma once
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <sstream>
enum class ProcessState {
    NEW,
    WAIT,
    RUNNING,
    BLOCKED,
    FINISHED,
    TERMINATED
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
        std::vector<int> max_registers;
        int uid;
        int memory;
        int arrivaltime;
        PCB* next;
        int timetoprocess;
    public:
        PCB(int id, int prio, int TTP, int arrival, int memory, int UID=0, PCB *nextPCB = NULL, int parent = 0)
                : pid(id), priority(prio), ppid(parent), arrivaltime(arrival), memory(memory), uid(UID), timetoprocess(TTP), next(nextPCB), state(ProcessState::NEW), programCounter(0), registers(8, 0),max_registers(8,0) {};

        ~PCB() = default;
        // ------------ 基本信息接口 ------------
        int getPID() const { return pid; }

        int getPriority() const { return priority; }

        int getPPID() const { return ppid; }

        PCB* getNextPCB() const {return next;}

        int gettimetoprocess() const {return timetoprocess;}

        ProcessState getState() const { return state; }

        int getPC() const { return programCounter; }

        void setPriority(int p) { priority = p; }

        int getArrivalTime(int t) { return arrivaltime;}

        // ------------ 状态管理 ------------
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
