#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include<regex>
#include "process.h"
#include "filesystem.h"
#include "globaldefinitions.h"

// Recebe vetor dos processos a partir do parser e instancia eles no vetor de processos instanciados
void ProcessInstantiator (std::vector<std::vector<std::string>> parsedProcesses, std::vector<Process>* instantiatedProcesses) {
    for(int i = 0; i<(int)parsedProcesses.size(); i++){
        Process p(
            i,
            stoi(parsedProcesses[i][0]),
            stoi(parsedProcesses[i][1]),
            stoi(parsedProcesses[i][2]),
            stoi(parsedProcesses[i][3]),
            stoi(parsedProcesses[i][4]),
            stoi(parsedProcesses[i][5]),
            stoi(parsedProcesses[i][6]),
            stoi(parsedProcesses[i][7])
        );
        instantiatedProcesses->push_back(p);
    }
}

// Cria o vetor de disk a partir do tamanho e dos files iniciais onde quem criou é -1
std::vector<std::pair<std::string, int>> DiskInstantiator (int diskBlocksCount, std::vector<std::vector<std::string>> parsedFileLines) {
    std::vector<std::pair<std::string,int>> disk(diskBlocksCount, {"0", -1});

    for(int i=0; i < (int)parsedFileLines.size(); i++){
        int start = stoi(parsedFileLines[i][1]);
        int size = stoi(parsedFileLines[i][2]);

        for(int j=start; j < start+size; j++)
            disk[j] = {parsedFileLines[i][0], -1};
    }
    return disk;
}

// retorna o arquivo de files.txt em uma tupla de {diskBlocksCount, operations, inicialização}
std::tuple<int, std::vector<std::vector<std::string>>, std::vector<std::vector<std::string>>> ParseFilesFile (std::string filesFilename) {
    int diskBlocksCount, diskSegmentsFilled;
    std::vector<std::vector<std::string>> parsedFileLines;
    std::vector<std::vector<std::string>> parsedOperationLines;

    std::string line;
    std::ifstream file;
    file.open(filesFilename);

    // quantidade de blocos do disco
    std::getline(file, line);
    diskBlocksCount = stoi(line);

    // quantidade de blocos ocupados
    std::getline(file, line);
    diskSegmentsFilled = stoi(line);

    // arquivos salvos no disco incialmente
    while (std::getline(file, line)) {
        std::vector<std::string> parsedFileLine = split(line, ", ");
        if (diskSegmentsFilled-- > 0)
            parsedFileLines.push_back(parsedFileLine);                            
    }
    // operacoes programadas do sistema de arquivos
    while (std::getline(file, line)) {
        std::vector<std::string> parsedOperationLine = split(line, ", ");
        parsedOperationLines.push_back(parsedOperationLine);
    }

    return {diskBlocksCount, parsedFileLines, parsedOperationLines};
}

// retorna o parse do arquivo de processos;
std::vector<std::vector<std::string>> ParseProcessesFile (std::string processesFilename) {
    std::vector<std::vector<std::string>> parsedProcessLines;

    std::string line;
    std::ifstream file;
    file.open(processesFilename);

    while (std::getline(file, line)) {
        std::vector<std::string> parsedLine = split(line,", ");
        parsedProcessLines.push_back(parsedLine);
    }
    return parsedProcessLines;
}

int main (int argc, char *argv[]) {
    std::string processesFilename, filesFilename;

    processesFilename = argv[argc-2];
    filesFilename = argv[argc-1];

    std::tuple<int, std::vector<std::vector<std::string>>, std::vector<std::vector<std::string>>> filesDescriptor = ParseFilesFile(filesFilename);
    std::vector<std::pair<std::string, int>> disk = DiskInstantiator(std::get<0>(filesDescriptor), std::get<1>(filesDescriptor));
    std::vector<std::tuple<int, int, int, int, bool>> log;
    FileSystem fs(disk, log);


    return 0;
}