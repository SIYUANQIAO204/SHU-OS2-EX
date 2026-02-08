#include <iostream>
#include "src/sys/sys.h"
#include "src/VirtualProcess/VirtualProcess.h"
#include "src/VirtualProcess/ProcessGenerater.h"
/*本程序用于期中验收，内容包括进程调度，虚存访问以及资源请求及死锁避免
 * 系统初始化由于调试等原因没写成函数，可以后续集成一下
 * 进程都以时间片为基础的服务时间单位，有时钟轮转和优先队列两种策略
 * 死锁避免采用银行家算法
 * 参数说明，设定块大小为1024，总共有64个块，最多支持4个并发线程，一共有四种资源，每种资源总量十个，进程总共有16个，平均分布在4个就绪队列中
 *
*/
int main() {
    sys::sys* system =new sys::sys();//可以改智能指针
    for(int i = 0;i < 4;i++)
    {
        system->addResource(10);
    }
    for(int i=0;i<2;i++)
    {
        system->addProceeManager(PCB_Sta::clock);
        system->addProceeManager(PCB_Sta::prio);
    }
    auto process_generator = VP::RandomProcessGenerator(1024);
    for(int i=0;i<16;i++)
    {
        auto temp = process_generator.generateRandomProcessParams(
                i, 16, 1024*10, 5, 4, 4,
                10, 4);
        system->creatProcess(temp.pid, temp.prio, temp.memory, temp.time_needed, temp.Blocknum, temp.strategy,
                             temp.max_needed, 0, temp.CPU);
    }
    //system->creatProcess(1,1,128*1024,1,64,Memory_Sat::LRU,std::vector(0,4),0);
    //初始化结束，正式开始运行
    int choice;
    std::cout<<"1: VMtest and Process test\n2: DeadLock test\n";
    std::cin>>choice;
    if(choice == 1)
    {
        /*为了方便展示，进程调度和会选取待处理进程最多的处理器
         * 每次运行会给出当前的运行的进程编号，内存访问序列（包含是否命中）
         * */
        int CPU = system->choosePCBchainWithMaxProcess();
        std::vector<int> opt_hit;
        while(!system->PCBchainEmpty(CPU))
        {
            system->run(CPU);
            int VMpasges = system->getHeadBlockNum(CPU);
            std::vector<int> access_sequencce = VP::generatePageAccessSequence(VMpasges,128);
            auto q = system->getProcessBlockNumAndVMnum(CPU);
            if(q == std::nullopt) continue;
            opt_hit.push_back(memory::OPTPageHitCount(access_sequencce,q->second,q->first));
            std::cout<<"OPT hit num is "<<opt_hit.back()<<'\n';
            std::cout<<"Visit sequence is: ";
            for(auto p:access_sequencce)
            {
                std::cout<<p<<' ';
            }
            std::cout<<'\n';
            for(auto p:access_sequencce)
            {
                std::cout<<"Visit VMpage id "<<p<<'\n';
                std::cout<<"VMpage address is "<<system->visitVM(p,CPU)<<'\n';
            }
            std::cout<<"Process finish\n";
            system->finish(CPU);
            std::cout<<"Run next Process\n";
        }
        std::cout<<"All process finish\n";
    }
    else if(choice == 2){
        for(int i=0;i<4;i++)
        {
            if(system->PCBchainEmpty(i))
            {
                auto temp = process_generator.generateRandomProcessParams(
                        i+16, 16, 1024*8, 5, 4, 4,
                        10, 4);
                system->creatProcess(temp.pid, temp.prio, temp.memory, temp.time_needed, temp.Blocknum, temp.strategy,
                                     temp.max_needed, 0, i);
            }
            system->run(i);
        }
        int unfinished = 4;
        while(unfinished > 0)
        {
            auto req = VP::generateRandomResourceRequest(system->getDeadLockProcess(),system->getAllocation(),system->getMaxNeed(),system->getAvailable());
            int i=0;
            if(req == std::nullopt) continue;
            for(;i< system->getPIDChainNum();i++)
            {
                if(system->getHeadPid(i) == req->first) break;
            }
            system->allocateResource(req->second,i);
            if(system->checkAndFinish(i)) unfinished--;
        }
        std::cout<<"All process finish\n";
    }
}
