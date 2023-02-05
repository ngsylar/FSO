<<<<<<< HEAD
#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include<regex>
#include "process.h"
#include "filesystem.h"
=======
#include "globaldefinitions.h"
>>>>>>> 3415422ecf5e00040034d1c30d1f7aa373e1e018

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
<<<<<<< HEAD
std::vector<std::pair<std::string,int>> diskInstantiator(int size, std::vector<std::vector<std::string>> parsedFiles){
    std::vector<std::pair<std::string,int>> f(size, {"0", -1});
    for(int i = 0; i<(int)parsedFiles.size(); i++){
        int start = std::stoi(parsedFiles[i][1]);
        int size = std::stoi(parsedFiles[i][2]);
        for(int j = start;j<start+size; j++){
            f[j] = {parsedFiles[i][0],-1};
        }
=======
std::vector<std::pair<std::string, int>> DiskInstantiator (int diskBlocksCount, std::vector<std::vector<std::string>> parsedFileLines) {
    std::vector<std::pair<std::string,int>> disk(diskBlocksCount, {"0", -1});

    for(int i=0; i < (int)parsedFileLines.size(); i++){
        int start = stoi(parsedFileLines[i][1]);
        int size = stoi(parsedFileLines[i][2]);

        for(int j=start; j < start+size; j++)
            disk[j] = {parsedFileLines[i][0], -1};
>>>>>>> 3415422ecf5e00040034d1c30d1f7aa373e1e018
    }
    return disk;
}
<<<<<<< HEAD
// retorna o arquivo de files.txt em uma tupla de {size, operações, inicialização}
std::tuple<int, std::vector<std::vector<std::string>>, std::vector<std::vector<std::string>>> parseFiles(std::string filesPath){
    int size;
    int occupied;
    int aux;
    std::vector<std::vector<std::string>> parsed;
    std::vector<std::vector<std::string>> parsedInit;
    std::ifstream file;
=======

// retorna o arquivo de files.txt em uma tupla de {diskBlocksCount, operations, inicialização}
std::tuple<int, std::vector<std::vector<std::string>>, std::vector<std::vector<std::string>>> ParseFilesFile (std::string filesFilename) {
    int diskBlocksCount, diskSegmentsFilled;
    std::vector<std::vector<std::string>> parsedFileLines;
    std::vector<std::vector<std::string>> parsedOperationLines;

>>>>>>> 3415422ecf5e00040034d1c30d1f7aa373e1e018
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

    std::tuple<int, std::vector<std::vector<std::string>>, std::vector<std::vector<std::string>>> parsedFiles = parseFiles(file_name);

    std::vector<std::pair<std::string,int>> disk = diskInstantiator(std::get<0>(parsedFiles), std::get<2>(parsedFiles));
    std::vector<std::tuple<int, int, int, int, bool>> log;
    FileSystem fs(disk, log);

    
    return 0;
}