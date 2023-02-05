#include "IOManager.h"

IO::IO(){
    printers = std::vector<int>(2,-1);
    SATAs = std::vector<int>(2,-1);
    sem_init(&(this->printer1), 0, 1);    
    sem_init(&(this->SATA1), 0, 1);    
    sem_init(&(this->printer2), 0, 1);    
    sem_init(&(this->SATA2), 0, 1);    
    sem_init(&(this->scanner), 0, 1);    
    sem_init(&(this->modem), 0, 1);
}
void IO::useModem(int pid){
    sem_wait(&(this->modem));
    this->modemPID = pid;
}
void IO::usePrinter(int pid,int id){
    switch(id){
        case 1:
            sem_wait(&(this->printer1));
            this->printers[0] = pid;
            break;
        case 2:
            sem_wait(&(this->printer2));
            this->printers[1] = pid;
            break;
        default:
            break;
    }
}
void IO::useSATA(int pid,int id){
    switch(id){
        case 1:
            sem_wait(&(this->SATA1));
            this->SATAs[0] = pid;
            break;
        case 2:
            sem_wait(&(this->SATA2));
            this->SATAs[1] = pid;
            break;
        default:
            break;
    }
}
void IO::useScanner(int pid){
    sem_wait(&(this->scanner));
    this->scannerPID = pid;
}
void IO::freeScanner(){
    sem_post(&(this->scanner));
    this->scannerPID = -1;
}
void IO::freeModem(){
    sem_post(&(this->modem));
    this->modemPID = -1;
}
void IO::freePrinter(int id){
    switch(id){
        case 1:
            sem_post(&(this->printer1));
            this->printers[0] = -1;
            break;
        case 2:
            sem_post(&(this->printer2));
            this->printers[1] = -1;
            break;
        default:
            break;
    }
}
void IO::freeSATA(int id){
    switch(id){
        case 1:
            sem_post(&(this->SATA1));
            this->SATAs[0] = -1;
            break;
        case 2:
            sem_post(&(this->SATA2));
            this->SATAs[1] = -1;
            break;
        default:
            break;
    }
}
bool IO::checkUsingScanner(int pid){
    return this->scannerPID == pid;
}
bool IO::checkUsingPrinter(int pid,int id){
    return this->printers[id] == pid;
}
bool IO::checkUsingModem(int pid){
    return this->modemPID == pid;
}
bool IO::checkUsingSATA(int pid,int id){
    return this->SATAs[id] == pid;
}