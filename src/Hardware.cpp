#include "globaldefinitions.h"

std::vector<std::pair<std::string, int>> Hardware::disk;
std::vector<int> Hardware::memory;
sem_t Hardware::scanner;
sem_t Hardware::printer0;
sem_t Hardware::printer1;
sem_t Hardware::modem;
sem_t Hardware::sata0;
sem_t Hardware::sata1;