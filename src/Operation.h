#ifndef OPERATION_H
#define OPERATION_H
class Operation {
    public:
        Operation();
        Operation(
            int id, 
            int pid, 
            int opcode, 
            std::string file_name, 
            int file_size);
        int getId();
        int getPid();
        int getOpcode();
        std::string getFileName();
        int getFileSize();
        enum operation_status{
            NONE,
            WAITING,
            EXECUTING,
            FAILED,
            SUCCESS
        };
        operation_status status;

    private:
        int id;
        int pid;
        int opcode;
        std::string file_name;
        int file_size;
};
#endif