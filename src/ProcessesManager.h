#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include<regex>
#include<queue>
#include "Process.h"
class ProcessManager {
    private:
        std::vector<std::vector<Process>> readyProcesses;
        void updateWaits();
        void checkWait();
        int max_wait;
    public:
        ProcessManager(int max_wait):readyProcesses(4){}
        void cycleQueues();
        bool insertProcess(Process process);
};