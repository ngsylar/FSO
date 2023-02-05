#include "globaldefinitions.h"

std::vector<Process> Dispatcher::instantiatedProcesses;
int Dispatcher::clock = 0;

void Dispatcher::Start (MemoryManager* memoryManager, ProcessesManager* processesManager) {
    Parser::ProcessInstantiator(Parser::processesDescriptor);
    std::sort(instantiatedProcesses.begin(), instantiatedProcesses.end(),
        [&](Process A, Process B){ A.getInitTime() < B.getInitTime(); });

    // editar: mudar condicao
    while (true) {
        while (not instantiatedProcesses.empty()) {
            Process& process = instantiatedProcesses.front();

            if (process.getInitTime() >= clock) {
                memoryManager->Allocate(&process);
                if (process.getPid() != -1)
                    processesManager->insertProcess(process);
                instantiatedProcesses.erase(instantiatedProcesses.begin());
            } else break;
        }
        clock++;
    }
}