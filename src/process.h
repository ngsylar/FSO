class Process {
    public:
        Process();
        Process(
            int pid,
            int init_time,
            int priority,
            int exec_time,
            int alloc_mem_blocks,
            int printer_code,
            int scan_req,
            int modem_req,
            int disk_num);
        int getRemainingTime();
        void resetRunTime();
        void updateRunTime(int executed_time);
        int getPid();
        int getInitTime();
        int getPriority();
        int getExecTime();
        int getRunTime();
        int getAllocMemBlocks();
        int getPrinterCode();
        int getScanReq();
        int getModemReq();
        int getDiskNum();
    private:
        int pid;
        int init_time;
        int priority;
        int exec_time;
        int run_time;
        int alloc_mem_blocks;
        int printer_code;
        int scan_req;
        int modem_req;
        int disk_num;
};