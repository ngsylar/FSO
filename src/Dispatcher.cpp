#include "globaldefinitions.h"

int Dispatcher::clock = 0;
std::vector<Process> Dispatcher::instantiatedProcesses;
std::vector<std::tuple<int, Process, int>> Dispatcher::logProcesses;
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
            if (processesManager->queuesAreEmpty())
                break;

        // se nova instancia de processo chegou, tenta alocar memoria
        } else {
            std::vector<Process>::iterator it = instantiatedProcesses.begin();
            do {
                Process newProcess = *it;
                if (newProcess.getInitTime() <= clock) {
                    int newProcessAddress = memoryManager->Allocate(&newProcess);

                    // se conseguiu alocar memoria, processo eh criado
                    if (newProcess.getPid() != -1){
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

                        logProcesses.push_back(std::make_tuple(clock, newProcess, newProcessAddress));
                        it = instantiatedProcesses.erase(instantiatedProcesses.begin());
                    } else it++;
                } else break;
            } while (it != instantiatedProcesses.end());
        }
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
    for (auto& log_p: logProcesses) {
        Process& process = std::get<1>(log_p);
        std::cout << "dispatcher at time" << std::get<0>(log_p) << " =>\n";
        std::cout << "\tPID: " << process.getPid() << "\n";
        std::cout << "\toffset: " << std::get<2>(log_p) << "\n";
        std::cout << "\tblocks: " << process.getAllocMemBlocks() << "\n";
        std::cout << "\tpriority: " << process.getPriority() << "\n";
        std::cout << "\ttime: " << process.getExecTime() << "\n";
        std::cout << "\tprinter: " << process.getPrinterCode() << "\n";
        std::cout << "\tscanner: " << process.getScanReq() << "\n";
        std::cout << "\tmodem: " << process.getModemReq() << "\n";
        std::cout << "\tdrive: " << process.getDiskNum();
        std::cout << std::endl << std::endl;

        // std::cout << "process " << process.getPid() << " =>\n";
        // std::cout << "\tP" << process.getPid() << "STARTED\n";
        // std::sort(logOperations.begin(), logOperations.end(),
        // [&](std::pair<int, Operation> A, std::pair<int, Operation> B) {
        //     return (A.second.getId() < B.second.getId());
        // });
        // int lastOperationId = 0;
        // for (auto& log_o: logOperations) {
        //     std::cout << "\tP" << process.getPid() << " instruction " << 
        // }
    }
}