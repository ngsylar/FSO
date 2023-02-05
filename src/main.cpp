#include "globaldefinitions.h"

int main (int argc, char *argv[]) {
    std::string processesFilename, filesFilename;
    processesFilename = argv[argc-2];
    filesFilename = argv[argc-1];

    Parser::ParseInputFiles(processesFilename, filesFilename);
    Hardware::disk = Parser::DiskInstantiator(Parser::diskBlocksCount, Parser::filesDescriptor);

    MemoryManager memoryManager;
    ProcessesManager processesManager(0); // editar: chutei um valor, nao sei o que deve ser passado 

    Dispatcher::Start(&memoryManager, &processesManager);
    Dispatcher::PrintLog();

    return 0;
}