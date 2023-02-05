#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "cpplibraries.h"
#include "MemoryManager.h"
#include "ProcessesManager.h"
#include "Process.h"
#include "Operation.h"

class Dispatcher {
    private:
        static std::vector<Process> instantiatedProcesses;
        static int clock;

        // logs
        static std::vector<std::pair<int, Process>> logProcesses;
        static std::vector<std::pair<int, Operation>> logOperations;

    public:
        static void Start(
            MemoryManager* memoryManager,
            ProcessesManager* processesManager
        );
        static void PrintLog();

    friend class Parser;
};

#endif