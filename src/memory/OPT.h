<<<<<<< HEAD
//
// Created by qiao on 25-12-19.
//
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <limits>
#pragma once
namespace memory {
    inline int OPTPageHitCount(const std::vector<int> &pages,
                        int virtualPageCount,
                        int frameCount) {
        if (frameCount <= 0)
            throw std::invalid_argument("frameCount must be > 0");

        std::vector<int> frames;
        int hitCount = 0;

        for (size_t i = 0; i < pages.size(); ++i) {
            int page = pages[i];

            // 合法性检查
            if (page < 0 || page >= virtualPageCount)
                throw std::out_of_range("Page number out of virtual memory range");

            auto it = std::find(frames.begin(), frames.end(), page);
            if (it != frames.end()) {
                hitCount++;
                continue;
            }

            if ((int) frames.size() < frameCount) {
                frames.push_back(page);
            } else {
                int replaceIndex = -1;
                int farthestUse = -1;

                for (int f = 0; f < frameCount; ++f) {
                    int nextUse = std::numeric_limits<int>::max();

                    for (size_t j = i + 1; j < pages.size(); ++j) {
                        if (pages[j] == frames[f]) {
                            nextUse = (int) j;
                            break;
                        }
                    }

                    if (nextUse > farthestUse) {
                        farthestUse = nextUse;
                        replaceIndex = f;
                    }
                }

                frames[replaceIndex] = page;
            }
        }

        return hitCount;
    }
=======
//
// Created by qiao on 25-12-19.
//
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <limits>
#pragma once
namespace memory {
    inline int OPTPageHitCount(const std::vector<int> &pages,
                        int virtualPageCount,
                        int frameCount) {
        if (frameCount <= 0)
            throw std::invalid_argument("frameCount must be > 0");

        std::vector<int> frames;
        int hitCount = 0;

        for (size_t i = 0; i < pages.size(); ++i) {
            int page = pages[i];

            // 合法性检查
            if (page < 0 || page >= virtualPageCount)
                throw std::out_of_range("Page number out of virtual memory range");

            auto it = std::find(frames.begin(), frames.end(), page);
            if (it != frames.end()) {
                hitCount++;
                continue;
            }

            if ((int) frames.size() < frameCount) {
                frames.push_back(page);
            } else {
                int replaceIndex = -1;
                int farthestUse = -1;

                for (int f = 0; f < frameCount; ++f) {
                    int nextUse = std::numeric_limits<int>::max();

                    for (size_t j = i + 1; j < pages.size(); ++j) {
                        if (pages[j] == frames[f]) {
                            nextUse = (int) j;
                            break;
                        }
                    }

                    if (nextUse > farthestUse) {
                        farthestUse = nextUse;
                        replaceIndex = f;
                    }
                }

                frames[replaceIndex] = page;
            }
        }

        return hitCount;
    }
>>>>>>> 320bfbd07e519d91666d3598d3577053a0f562b8
}