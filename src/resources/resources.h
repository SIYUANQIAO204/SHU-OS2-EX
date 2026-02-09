
//
// Created by qiao on 25-12-7.
//
/*用于模拟资源的类，包括资源的大小，资源的分配情况以及资源被占用的数量
 *函数包括分配给某个进程一定数量的资源，回收某个进程所有或者一定数量的资源
 */

#ifndef OS_RESOURCES_H
#define OS_RESOURCES_H
#pragma once
#include <vector>
#include <algorithm>

namespace resource{
    class resources{
    private:
        int size;
        std::vector<std::pair<int,int>> opy;
        int opied;
    public:
        resources(int maxsize,std::vector<std::pair<int,int>> allo={}, int oppy = 0)
        : size(maxsize), opy(allo), opied(oppy){};
        ~resources() = default;
        bool allocate(int pid, int num)
        {
            if (num + opied > size)
                return false;

            auto it = std::lower_bound(
                    opy.begin(), opy.end(), pid,
                    [](const auto& p, int v) {
                        return p.first < v;
                    }
            );

            if (it != opy.end() && it->first == pid) {
                it->second += num;
            } else {
                opy.insert(it, {pid, num});
            }

            opied += num;
            return true;
        }

        void release(int pid)
        {
            auto  temp = std::upper_bound(opy.begin(),opy.end(),std::make_pair(pid,0));
            if(temp == opy.end() || temp->first != pid)
            {
                return;
            }
            else
            {
                opied -= temp->second;
                opy.erase(temp);
            }
            return;
        }

        void release(int pid,int num)
        {
            auto  temp = std::upper_bound(opy.begin(),opy.end(),std::make_pair(pid,0));
            if(temp == opy.end() || temp->first != pid)
            {
                return;
            }
            else
            {
                opied -= temp->second;
                if(temp->second<=num) opy.erase(temp);
                else temp->second-=num;
            }
            return;
        }

        int getsize() const { return size;}
        int getopy() const {return opied;}
    };
}
#endif //OS_RESOURCES_H

