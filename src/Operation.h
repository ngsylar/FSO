#ifndef OPERATION_H
#define OPERATION_H

#include "cpplibraries.h"

class Operation {
    public:
        enum operation_status {NONE, WAITING, EXECUTING, SUCCESS, FAILURE};

        Operation(int id, int pid, int opcode, std::string file_name, int file_size);
        operation_status status;

    private:
        int id;
        int pid;
        int opcode;
        std::string file_name;
        int file_size;
};

#endif