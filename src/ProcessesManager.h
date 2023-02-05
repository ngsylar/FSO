#ifndef PROCESSES_MANAGER_H
#define PROCESSES_MANAGER_H

#include "cpplibraries.h"

#include "Process.h"
#include "Operation.h"

class ProcessesManager {
    private:
        std::vector<std::vector<Process>> readyProcesses;
        void updateWaits();
        void checkWait();
        int max_wait;
        Operation cycleQueues();
    public:
        // executa ciclo das filas
        Operation run(){}
        // max wait é o tempo de espera maximo de um processo antes dele aumentar a prioridade
        ProcessesManager(int max_wait):readyProcesses(4){}
        // Adiciona processa em alguma das filas
        bool insertProcess(Process process);
};

#endif