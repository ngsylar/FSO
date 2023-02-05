#ifndef HARDWARE_H
#define HARDWARE_H

#include "cpplibraries.h"

class Hardware {
    public:
        static std::vector<std::pair<std::string, int>> disk;
        static std::vector<int> memory;
        static sem_t scanner;
        static sem_t printer0;
        static sem_t printer1;
        static sem_t modem;
        static sem_t sata0;
        static sem_t sata1;
};

#endif