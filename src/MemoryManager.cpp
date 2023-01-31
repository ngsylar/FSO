#include "GlobalDefinitions.h"

MemoryManager::MemoryManager () {
    blocksCount = 1024;
    realTimeBlocksCount = 64;
    memory = std::vector<int>(blocksCount);
    segmentsBegin = new Segment(false, 0, 1024);
}

MemoryManager::Segment::Segment (bool filled, int address, int size, Segment* nextSegment) {
    this->filled = filled;
    this->address = address;
    this->size = size;
    this->nextSegment = nextSegment;
}

MemoryManager::~MemoryManager () {
    Segment* currentSegment,* nextSegment;
    currentSegment = segmentsBegin;
    do {
        nextSegment = currentSegment->nextSegment;
        delete(currentSegment);
    } while (nextSegment != nullptr);
}

bool MemoryManager::Allocate (int pid, int blocksCount) {
    Segment* currentSegment = segmentsBegin;
    while (currentSegment != nullptr) {
        if ((not currentSegment->filled) and (currentSegment->size >= blocksCount)) {
            
            int nextSegmentAddress = currentSegment->address + blocksCount;
            for (int i = currentSegment->address; i < nextSegmentAddress; i++)
                memory[i] = pid;
            currentSegment->filled = true;
            
            if (currentSegment->size > blocksCount) {
                int newSegmentSize = currentSegment->size - blocksCount;
                currentSegment->size = blocksCount;

                Segment* newSegment = new Segment(
                    false, nextSegmentAddress, newSegmentSize, currentSegment->nextSegment
                );
                currentSegment->nextSegment = newSegment;
            }
            return true;
        }
        currentSegment = currentSegment->nextSegment;
    }
    return false;
}

void MemoryManager::Deallocate (int pid) {}

int MemoryManager::GetSize () {
    return blocksCount;
}

int MemoryManager::GetRealTimeSize () {
    return realTimeBlocksCount;
}

int MemoryManager::GetUserSize () {
    return (blocksCount - realTimeBlocksCount);
}