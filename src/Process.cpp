#include "globaldefinitions.h"

Process::Process(int pid, int init_time, int priority, int exec_time, int alloc_mem_blocks, int printer_code, int scan_req, int modem_req, int disk_num)
{
    this->pid = pid;
    this->run_time = 0;
    this->init_time = init_time;
    this->priority = priority;
    this->exec_time = exec_time;
    this->alloc_mem_blocks = alloc_mem_blocks;
    this->printer_code = printer_code;
    this->scan_req = scan_req;
    this->modem_req = modem_req;
    this->disk_num = disk_num;
    this->wait = 0;
}
Process::Process()
{
}
void Process::resetRunTime()
{
    this->run_time = 0;
}
int Process::getRemainingTime()
{
    return this->exec_time-this->run_time;
}
void Process::incrementWait(){
    this->wait++;
}
void Process::updateRunTime(int executed_time)
{
    this->run_time += executed_time;
}
void Process::updateWait(int new_wait){
    this->wait = new_wait;
}
void Process::setPriority(int new_priority){
    this->priority = new_priority;
}
int Process::getWait(){
    return this->wait;
}
int Process::getPid(){
   return this->pid;
}
int Process::getInitTime(){
    return this->init_time;
}
int Process::getPriority(){
    return this->priority;
}
int Process::getExecTime(){
    return this->exec_time;
}
int Process::getRunTime(){
    return this->run_time;
}
int Process::getAllocMemBlocks(){
    return this->alloc_mem_blocks;
}
int Process::getPrinterCode(){
    return this->printer_code;
}
int Process::getScanReq(){
    return this->scan_req;
}
int Process::getModemReq(){
    return this->modem_req;
}
int Process::getDiskNum(){
    return this->disk_num;
}