#ifndef PARSER_H
#define PARSER_H

#include "cpplibraries.h"

class Parser {
    private:
        // analisador dos arquivos de entrada
        static void ParseProcessesFile (std::string processesFilename);
        static void ParseFilesFile (std::string filesFilename);

    public:
        // arquivos analisados
        static int diskBlocksCount;
        static std::vector<std::vector<std::string>> filesDescriptor;
        static std::vector<std::vector<std::string>> operationDescriptor;
        static std::vector<std::vector<std::string>> processesDescriptor;

        // analisador geral
        static void ParseInputFiles(std::string processesFilename, std::string filesFilename);

        // instanciador de objetos descritos pelos arquivos analisados
        static std::vector<std::pair<std::string, int>> DiskInstantiator (int diskBlocksCount, std::vector<std::vector<std::string>> parsedFileLines);
        static void ProcessInstantiator (std::vector<std::vector<std::string>> parsedProcesses);
};

#endif