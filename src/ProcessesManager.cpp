#include "ProcessesManager.h"

// executa um processo da fila de processos e se precisar, realimenta a fila 
Operation execProcess(std::vector<std::vector<Process>>* readyProcesses, int queue, IO io, FileSystem fs){
    Process tempProcess = (*readyProcesses)[queue].front();
    Operation op;
    if(tempProcess.getPriority()){
        (*readyProcesses)[queue].erase((*readyProcesses)[queue].begin());
        // se ainda falta executar, aumenta o tempo de exec e realimenta a fila zerando o wait
        op = tempProcess.run(io,fs);
        if(op.status == op.EXECUTING || op.status == op.WAITING){
            (*readyProcesses)[tempProcess.getPriority()].push_back(tempProcess);
        }
    } else {
        op = tempProcess.run(io,fs);
        if(op.status != op.EXECUTING && op.status != op.WAITING){
            (*readyProcesses)[queue].erase((*readyProcesses)[queue].begin());
        }
    }
    return op;
}

ProcessManager::ProcessManager(int max_wait){
    readyProcesses = std::vector<std::vector<Process>>(4);
    this->max_wait = max_wait;
    this->readyProcesses = std::vector<std::vector<Process>>(4);
}
bool ProcessesManager::insertProcess(Process process){
    if(this->readyProcesses[process.getPriority()].size()<1000){
        this->readyProcesses[process.getPriority()].push_back(process); 
        return true;
    } else {
        return false;
    }
}
// Escolhe um processo para realizar
Operation ProcessesManager::cycleQueues(IO io, FileSystem fs){
    // Verifica fila de tempo real
    if(this->readyProcesses[0].size()){
        return execProcess(&(this->readyProcesses), 0, io, fs);
    }else {
        for(int i = 1; i<this->readyProcesses.size(); i++){
            if(this->readyProcesses[i].size()){
                return execProcess(&(this->readyProcesses), i, io, fs);
            }
        }
    }
    Operation op = Operation(-1,-1,-1,"",-1);
    op.status = op.NONE;
    return op;
}
Operation ProcessesManager::run(IO io, FileSystem fs){
    return this->cycleQueues(io, fs);
}
void ProcessesManager::updateWaits(){
    // começa em 1 para ignorar fila de tempo real
    for(int i = 1; i<this->readyProcesses.size(); i++){
        for(int j = 0; j<this->readyProcesses[i].size(); j++){
            // atualiza o wait de todos que estão na fila
            this->readyProcesses[i][j].incrementWait();
        }
    }
}
// Itera nas filas e gerencia as prioridades
void ProcessesManager::checkWait(){
    for(int i = 1; i <= 3; i++){
        for(int j = 0; j < this->readyProcesses[i].size(); j++){
            // aumenta a prioridade se o tempo de espera do processo for maior que o max_wait definido
            if(this->readyProcesses[i][j].getWait() > this->max_wait){    
                if(i>1){
                    // zera wait antes de mudar de fila
                    this->readyProcesses[i][j].updateWait(0);
                    this->readyProcesses[i-1].push_back(this->readyProcesses[i][j]);
                    //remove o processo da fila
                    this->readyProcesses[i].erase(this->readyProcesses[i].begin()+j);
                }
            }
        }
    }
}