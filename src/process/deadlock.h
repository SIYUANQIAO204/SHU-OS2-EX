//
// Created by qiao on 25-12-7.
//

#ifndef OS_DEADLOCK_H
#define OS_DEADLOCK_H
#include <utility>

#include "../resources/resources.h"
#include "vector"
#include "map"
#include "unordered_map"
namespace resource {
    class resourcesmanager {
    private:
        std::vector<resources> all_resources;
        int resources_num;
        std::vector<int> Max_resources;
        std::vector<int> Available_resources;
        std::vector<std::vector<int>> allocation;
        std::vector<std::vector<int>> Max_need;
        std::vector<int> process;
        std::unordered_map<int, int> pid2idx;
    public:
        resourcesmanager(std::vector<resources> resource)
        : all_resources(std::move(resource)){
            resources_num=(int) all_resources.size();
            for(int i = 0;i < resources_num;i++)
            {
                Max_resources.push_back(all_resources[i].getsize());
                Available_resources.push_back(all_resources[i].getsize() - all_resources[i].getopy());
            }
        }
        ~resourcesmanager() = default;
        bool  legalCheck(int pid, const std::vector<int>& require);
        bool safetyCheck(std::vector<int> work);
        bool allocateResources(int pid, std::vector<int> require);
        void releaseResources(int pid);
        void insertResources(const resources& res);
        void insertProcess(int pid, const std::vector<int>& max_registers = {}, const std::vector<int>& registers = {});
        inline bool allocationEmpty() {return allocation.empty();}
        bool meetneed(int pid);
        inline std::vector<std::vector<int>> getAllocation() const {return allocation;}
        inline std::vector<std::vector<int>> getMaxNeed() const {return Max_need;}
        inline std::vector<int> getAvailable() const {return Available_resources;}
        inline std::vector<int> getIndexToProcess() const {return process;}
        int getIndexByPid(int process);


    };
}

#endif //OS_DEADLOCK_H
