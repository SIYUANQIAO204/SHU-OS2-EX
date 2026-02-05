//
// Created by qiao on 25-12-11.
//

#ifndef OS_VIRTUALPROCESS_H
#define OS_VIRTUALPROCESS_H
#pragma once
#include <vector>
#include <random>
#include <algorithm>
#include <optional>
namespace VP {
    std::vector<int> generatePageAccessSequence(int numPages, int seqLen) {
        std::vector<int> seq;
        if (seqLen <= 0) return seq;

        if (numPages <= 0) {
            return seq;
        }
        if (numPages == 1) {
            seq.assign(seqLen, 0);
            return seq;
        }

        seq.reserve(seqLen);

        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<> distAll(0, numPages - 1);
        std::uniform_int_distribution<> distFront(0, numPages / 2 - 1);
        std::uniform_int_distribution<> distBack(numPages / 2, numPages - 1);
        std::uniform_real_distribution<> distProb(0.0, 1.0);

        auto clusteredRandom = [&](int center, int window) {
            int low  = std::max(0, center - window);
            int high = std::min(numPages - 1, center + window);
            if (low > high) return low;   // 双保险
            std::uniform_int_distribution<> dist(low, high);
            return dist(gen);
        };

        int current = distAll(gen);

        for (int i = 0; i < seqLen; ++i) {
            double r = distProb(gen);

            if (r < 0.5) {
                seq.push_back(current);

                if (distProb(gen) < 0.85) {
                    current = (current + 1) % numPages;
                } else {
                    current = clusteredRandom(current, 3);
                }

            } else if (r < 0.75) {
                int base = distFront(gen);
                seq.push_back(clusteredRandom(base, 2));

            } else {
                int base = distBack(gen);
                seq.push_back(clusteredRandom(base, 2));
            }
        }

        return seq;
    }

    std::optional<std::pair<int, std::vector<int>>>
    generateRandomResourceRequest(
            const std::vector<int>& idx2pid,
            const std::vector<std::vector<int>>& Allocation,
            const std::vector<std::vector<int>>& MaxNeed,
            const std::vector<int>& Available
    ) {
        int P = Allocation.size();
        if (P == 0) return std::nullopt;

        int R = Allocation[0].size();

        std::vector<std::vector<int>> Need(P, std::vector<int>(R));
        for (int i = 0; i < P; ++i)
            for (int j = 0; j < R; ++j)
                Need[i][j] = MaxNeed[i][j] - Allocation[i][j];

        std::vector<int> candidates;
        for (int i = 0; i < P; i++) {
            for (int j = 0; j < R; j++) {
                if (Need[i][j] > 0) {
                    candidates.push_back(i);
                    break;
                }
            }
        }

        if (candidates.empty())
            return std::nullopt;

        // RNG
        static std::mt19937 gen{ std::random_device{}() };
        std::uniform_int_distribution<> distProc(0, candidates.size() - 1);

        int idx = candidates[distProc(gen)];
        int pid = idx2pid[idx];

        std::vector<int> request(R, 0);
        bool nonzero = false;

        for (int r = 0; r < R; ++r) {
            int maxReq = std::min(Need[idx][r], Available[r]);
            if (maxReq > 0) {
                std::uniform_int_distribution<> dist(0, maxReq);
                request[r] = dist(gen);
                if (request[r] > 0) nonzero = true;
            }
        }

        if (!nonzero) {
            std::vector<int> valid;
            for (int r = 0; r < R; r++)
                if (Need[idx][r] > 0 && Available[r] > 0)
                    valid.push_back(r);

            if (!valid.empty()) {
                std::uniform_int_distribution<> distR(0, valid.size() - 1);
                int rr = valid[distR(gen)];
                request[rr] = 1;
            } else {
                return std::nullopt;
            }
        }

        return std::make_pair(pid, request);
    }


}
#endif //OS_VIRTUALPROCESS_H
