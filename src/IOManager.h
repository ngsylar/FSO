#ifndef IO_H
#define IO_H
#include "cpplibraries.h"
class IO {
    public:
        IO();
        void useScanner(int pid);
        void usePrinter(int pid,int id);
        void useModem(int pid);
        void useSATA(int pid,int id);
        void freeScanner();
        void freePrinter(int id);
        void freeModem();
        void freeSATA(int id);
        bool checkUsingScanner(int pid);
        bool checkUsingPrinter(int pid,int id);
        bool checkUsingModem(int pid);
        bool checkUsingSATA(int pid,int id);

    private:
        std::vector<int> printers;
        std::vector<int> SATAs;
        int modemPID;
        int scannerPID;
        sem_t printer1;
        sem_t SATA1;
        sem_t modem;
        sem_t scanner;
        sem_t printer2;
        sem_t SATA2;
};
#endif