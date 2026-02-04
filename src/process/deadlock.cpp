//
// Created by qiao on 25-12-7.
//

#include <cstring>
#include "deadlock.h"
namespace resource{

    int resourcesmanager::getIndexByPid(int pid) {
        auto it = pid2idx.find(pid);
        return (it != pid2idx.end()) ? it->second : -1;
    }

    bool resourcesmanager::legalCheck(int pid, const std::vector<int>& require) {
        if (require.size() != resources_num) return false;

        int idx = getIndexByPid(pid);
        if (idx == -1) return false;

        for (int i = 0; i < resources_num; i++) {
            int need = Max_need[idx][i] - allocation[idx][i];
            if (require[i] < 0 || require[i] > need)
                return false;
        }
        return true;
    }

    bool resourcesmanager::safetyCheck(std::vector<int> work) {
        int P = allocation.size();      // 进程数
        int R = work.size();            // 资源数

        std::vector<bool> finish(P, false);

        while (true) {
            bool found = false;

            for (int i = 0; i < P; i++) {
                if (finish[i]) continue;

                bool canRun = true;
                for (int r = 0; r < R; r++) {
                    int need = Max_need[i][r] - allocation[i][r];
                    if (need > work[r]) {
                        canRun = false;
                        break;
                    }
                }

                if (canRun) {
                    // 假设该进程完成，释放其资源
                    for (int r = 0; r < R; r++)
                        work[r] += allocation[i][r];

                    finish[i] = true;
                    found = true;
                }
            }

            if (!found) break;
        }

        // 所有进程都能完成 → 安全
        for (bool f : finish)
            if (!f) return false;

        return true;
    }

    bool resourcesmanager::allocateResources(int pid, std::vector<int> require) {
        if(!legalCheck(pid,require)){
            std::cout<<"illegal requirement"<<'\n';
            return false;
        }
        std::vector<int> temp = Available_resources;
        auto temp2 = allocation;
        int q = getIndexByPid(pid);
        if(q==-1) return false;
        for(int i=0;i < (int)require.size();i++)
        {
            if( require[i] > Available_resources[i])
            {
                std::cout<<"Lack resoureces,allocate fail"<<'\n';
                allocation = temp2;
                return false;
            }
            temp[i] -= require[i];
            allocation[q][i] +=require[i];
        }

        if(!this->safetyCheck(temp))
        {
            std::cout<<"Lack resources, allocate fail"<<'\n';
            allocation = temp2;
            return false;
        }
        Available_resources = temp;
        for(int i=0;i<(int)all_resources.size();i++)
        {
            all_resources[i].allocate(pid,require[i]);
        }
        std::cout<<"Allocate succeed\n";
        std::cout<<"process "<<pid<<" now get resources:\n";
        for(auto i:require) std::cout<<i<<' ';
        std::cout<<"\nprocess "<<pid<<" now has resources:\n";
        for(auto i:allocation[q]) std::cout<<i<<' ';
        std::cout<<'\n';
        return true;

    }

    void resourcesmanager::releaseResources(int pid) {
        int q = getIndexByPid(pid);
        if(q == -1) return;
        for(int i = 0;i < (int) Available_resources.size();i++)
        {
            Available_resources[i] += allocation[q][i];
            all_resources[i].release(pid);
        }
        allocation.erase(allocation.begin()+q);
        Max_need.erase(Max_need.begin()+q);
        process.erase(process.begin()+q);
        pid2idx.erase(pid);

        for (auto &kv : pid2idx) {
            if (kv.second > q) {
                kv.second--;
            }
        }
    }

    void resourcesmanager::insertResources(const resource::resources& res) {
        all_resources.push_back(res);
        Max_resources.push_back(res.getsize());
        resources_num++;
        Available_resources.push_back(res.getsize());
        for(auto p:allocation) p.push_back(0);
        for (auto p:Max_need) p.push_back(0);
    }

    void resourcesmanager::insertProcess(int pid, const std::vector<int>& max_registers, const std::vector<int>& registers) {
        int idx = process.size();          // 新进程位置
        process.push_back(pid);
        pid2idx[pid] = idx;
        if(!registers.empty())allocation.push_back(registers);
        else allocation.push_back(std::vector<int> (resources_num,0));
        if(!max_registers.empty()) Max_need.push_back(max_registers);
        else Max_need.push_back(std::vector<int> (resources_num,0));
    }

    bool resourcesmanager::meetneed(int pid) {
        int q;
        for(int i=0;i<(int)process.size();i++)
        {
            if(process[i]==pid){
                q = i;
                break;
            }
        }
        for(int i=0;i<resources_num;i++)
        {
            if(allocation[q][i] != Max_need[q][i])
            {
                return false;
            }
        }
        return true;
    }
}