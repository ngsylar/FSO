#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "cpplibraries.h"
#include "MemoryManager.h"
#include "ProcessesManager.h"

class Dispatcher {
    private:
        static std::vector<Process> instantiatedProcesses;
        static int clock;

    public:
        static void Start(
            MemoryManager* memoryManager,
            ProcessesManager* processesManager
        );

    friend class Parser;
};

#endif