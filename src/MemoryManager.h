#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include "CppLibraries.h"

class MemoryManager {
    private:
        class Segment;
        Segment* segmentsBegin;
        std::vector<int> memory;
        int blocksCount;
        int realTimeBlocksCount;
        int lastPid;
    
    public:
        MemoryManager();
        ~MemoryManager();
        int Allocate(int priority, int blocksCount);
        bool Deallocate(int pid, int address);
        int GetSize();
        int GetRealTimeSize();
        int GetUserSize();
};

class MemoryManager::Segment {
    public:
        bool filled;
        int address;
        int size;
        Segment* nextSegment;
    
        Segment(bool filled, int address, int size, Segment* nextSegment=nullptr);
};

#endif