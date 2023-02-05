#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include<regex>
#include<queue>
#include "Process.h"
#include "Operation.h"
class ProcessManager {
    private:
        std::vector<std::vector<Process>> readyProcesses;
        void updateWaits();
        void checkWait();
        int max_wait;
        Operation cycleQueues(IO io, FileSystem fs);
    public:
        // executa ciclo das filas
        Operation run(IO io, FileSystem fs);
        // max wait é o tempo de espera maximo de um processo antes dele aumentar a prioridade
        ProcessManager(int max_wait);
        // Adiciona processa em alguma das filas
        bool insertProcess(Process process);
};