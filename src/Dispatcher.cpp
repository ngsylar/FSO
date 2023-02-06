#include "globaldefinitions.h"

int Dispatcher::clock = 0;
std::vector<Process> Dispatcher::instantiatedProcesses;
std::vector<std::pair<int, Process>> Dispatcher::logProcesses;
std::vector<std::pair<int, Operation>> Dispatcher::logOperations;

void Dispatcher::Start (
    MemoryManager* memoryManager, ProcessesManager* processesManager, FileSystem* fileSystem
) {
    Parser::ProcessInstantiator(Parser::processesDescriptor);
    std::sort(instantiatedProcesses.begin(), instantiatedProcesses.end(),
        [&](Process A, Process B){ return (A.getInitTime() < B.getInitTime()); });

    while (true) {
        // se nao ha mais processos para serem criados e todas as operacoes foram concluidas, finalizar
        if (instantiatedProcesses.empty()) {
            std::cout << logOperations.size() << " " << Parser::operationDescriptor.size() << std::endl;
            if (logOperations.size() == Parser::operationDescriptor.size())
                break;
        } else do {
            // se nova instancia de processo chegou, tenta alocar memoria
            Process newProcess = instantiatedProcesses.front();
            if (newProcess.getInitTime() <= clock) {
                memoryManager->Allocate(&newProcess);

                // se conseguiu alocar memoria, processo eh criado
                if (newProcess.getPid() != -1)
                    for (int i=0; i < Parser::operationDescriptor.size(); i++)
                        if (stoi(Parser::operationDescriptor[i][0]) == newProcess.getPid()) {
                            Operation op(
                                i,
                                stoi(Parser::operationDescriptor[i][0]),
                                stoi(Parser::operationDescriptor[i][1]),
                                Parser::operationDescriptor[i][2],
                                stoi(Parser::operationDescriptor[i][3])
                            );
                            op.status = op.WAITING;
                            newProcess.insertOperation(&op);
                        }
                processesManager->insertProcess(newProcess);
                logProcesses.push_back(std::make_pair(clock, newProcess));
                instantiatedProcesses.erase(instantiatedProcesses.begin());
            } else break;
        } while (not instantiatedProcesses.empty());

        // continua o processamento
        Process process = processesManager->run(Hardware::IOmanager, *fileSystem);
        if (process.isFinished())
            memoryManager->Deallocate(process.getPid());

        // faz o log
        Operation operation = process.getRunningOp();
        if (operation.status & (Operation::SUCCESS | Operation::FAILED))
            logOperations.push_back(std::make_pair(clock, operation));

        clock++;
    }
}

void Dispatcher::PrintLog () {

}