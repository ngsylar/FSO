#include "globaldefinitions.h"

Operation::Operation(int id, int pid, int opcode, std::string file_name, int file_size)
{
    this->id = id;
    this->pid = pid;
    this->opcode = opcode;
    this->file_name = file_name;
    this->file_size = file_size;
}

Operation::Operation()
{
}

int Operation::getId(){
    return this->id;
}

int Operation::getPid(){
    return this->pid;
}

int Operation::getOpcode(){
    return this->opcode;
}

std::string Operation::getFileName(){
    return this->file_name;
}

int Operation::getFileSize(){
    return this->file_size;
}