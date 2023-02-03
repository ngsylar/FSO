#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include<regex>
#include<queue>
#include "Process.h"
#include "ProcessesManager.h"
ProcessManager::ProcessManager(int max_wait){
    this->max_wait = max_wait;
}
bool ProcessManager::insertProcess(Process process){
    this->readyProcesses[process.getPriority()].push_back(process); 
}
void ProcessManager::cycleQueues(){
    if(this->readyProcesses[0].size()){
        Process tempProcess = this->readyProcesses[0].front();
        this->readyProcesses[0].erase(this->readyProcesses[0].begin());
        // se for realimentar a fila, incrementa o wait
        if(tempProcess.getRemainingTime()){
            tempProcess.updateWait(0);
            this->readyProcesses[tempProcess.getPriority()].push_back(tempProcess);
        }
        //TODO: adicionar callback para indicar termino do processo
    }else {

    }
}
void ProcessManager::updateWaits(){
    // começa em 1 para ignorar fila de tempo real
    for(int i = 1; i<this->readyProcesses.size(); i++){
        for(int j = 0; j<this->readyProcesses[i].size(); j++){
            // atualiza o wait de todos que estão na fila
            this->readyProcesses[i][j].incrementWait();
        }
    }
}
// Itera nas filas e gerencia as prioridades
void ProcessManager::checkWait(){
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