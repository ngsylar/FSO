#include "ProcessesManager.h"

// executa um processo da fila de processos e se precisar, realimenta a fila 
void execProcess(std::vector<std::vector<Process>>* readyProcesses, int queue){
    Process tempProcess = (*readyProcesses)[queue].front();
    (*readyProcesses)[queue].erase((*readyProcesses)[queue].begin());
    // se ainda falta executar, aumenta o tempo de exec e realimenta a fila zerando o wait
    if(tempProcess.getRemainingTime()-1 > 0){
        tempProcess.updateRunTime(1);
        tempProcess.updateWait(0);
        (*readyProcesses)[tempProcess.getPriority()].push_back(tempProcess);
    }
}
ProcessesManager::ProcessesManager(int max_wait){
    this->max_wait = max_wait;
}
bool ProcessesManager::insertProcess(Process process){
    this->readyProcesses[process.getPriority()].push_back(process); 
}
// Escolhe um processo para realizar
Operation ProcessesManager::cycleQueues(){
    // Verifica fila de tempo real
    if(this->readyProcesses[0].size()){
        execProcess(&this->readyProcesses, 0);
        //TODO: adicionar callback para indicar termino do processo
    }else {
        for(int i = 1; i<this->readyProcesses.size(); i++){
            if(this->readyProcesses[i].size()){
                execProcess(&this->readyProcesses, i);
            }
        }
    }
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