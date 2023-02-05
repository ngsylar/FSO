#include "globaldefinitions.h"

std::vector<std::pair<std::string, int>> Hardware::disk;
std::vector<int> Hardware::memory;
int Hardware::scanner = -1;
int Hardware::printer[2] = {-1, -1};
int Hardware::modem = -1;
int Hardware::sata[2] = {-1, -1};