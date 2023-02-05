#include "filesystem.h"
#include "globaldefinitions.h"

int main (int argc, char *argv[]) {
    std::string processesFilename, filesFilename;
    processesFilename = argv[argc-2];
    filesFilename = argv[argc-1];

    Parser::ParseInputFiles(processesFilename, filesFilename);
    Hardware::disk = Parser::DiskInstantiator(Parser::diskBlocksCount, Parser::filesDescriptor);
    std::vector<std::tuple<int, int, int, int, bool>> log;

    MemoryManager memoryManager;
    ProcessesManager processesManager(3000);
    FileSystem fs(Hardware::disk, log);

    Dispatcher::Start(&memoryManager, &processesManager, &fs);
    Dispatcher::PrintLog();

    std::cout << "AAAAAAAAAAAAAAAAAAI";

    return 0;
}