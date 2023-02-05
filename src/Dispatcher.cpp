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
            if (logOperations.size() == Parser::operationDescriptor.size()) {
                break;
            }
        } else {
            // se nova instancia de processo chegou, tenta alocar memoria
            Process& process = instantiatedProcesses.front();
            if (process.getInitTime() <= clock) {
                memoryManager->Allocate(&process);

                // se conseguiu alocar memoria, processo eh criado
                if (process.getPid() != -1)
                    for (int i=0; i < Parser::operationDescriptor.size(); i++)
                        if (stoi(Parser::operationDescriptor[i][0]) == process.getPid()) {
                            Operation op(
                                i,
                                stoi(Parser::operationDescriptor[i][0]),
                                stoi(Parser::operationDescriptor[i][1]),
                                Parser::operationDescriptor[i][2],
                                stoi(Parser::operationDescriptor[i][3])
                            );
                            op.status = op.WAITING;
                            process.insertOperation(&op);
                        }
                processesManager->insertProcess(process);
                logProcesses.push_back(std::make_pair(clock, process));
                instantiatedProcesses.erase(instantiatedProcesses.begin());
            }
        }
        // continua o processamento
        Operation operation = processesManager->run(Hardware::IOmanager, *fileSystem);
        if ((operation.status == Operation::SUCCESS) or (operation.status == Operation::FAILED)) {
            logOperations.push_back(std::make_pair(clock, operation));
        }
        clock++;
    }
}

void Dispatcher::PrintLog () {

}