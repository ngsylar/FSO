class Operation {
    public:
        enum operation_status{
            FAILED,
            EXECUTING,
            SUCCESS
        };
        operation_status status;
    private:
        int id;
        int pid;
        int type;
        int file_name;
        int file_size;
};