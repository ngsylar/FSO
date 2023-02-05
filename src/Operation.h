class Operation {
    public:
        enum operation_status{
            FAILED,
            EXECUTING,
            SUCCESS
        };
    private:
        int id;
        int pid;
        int type;
        int file_name;
        int file_size;
        operation_status status;
};