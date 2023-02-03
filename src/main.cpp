#include<vector>
#include<string>
#include "process.h"
#include<fstream>
#include<iostream>
#include<regex>
#include<queue>

std::vector<std::string> split(std::string s,std::string separator){
    std::vector<std::string> res;

    std::regex r(separator);

    std::regex_token_iterator<std::string::iterator> regex_end;

    std::regex_token_iterator<std::string::iterator> splitted(s.begin(), s.end(), r, -1);

    while(splitted != regex_end) res.push_back(*splitted++);

    return res;

}
// Recebe vetor dos processos a partir do parser e instancia eles no vetor de processos instanciados
std::vector<Process> processInstantiator(std::vector<std::vector<std::string>> parsedProcesses){
    std::vector<Process> instantiatedProcesses;
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
        instantiatedProcesses.push_back(p);
    }
    return instantiatedProcesses;
}
// Cria o vetor de disk a partir do tamanho e dos files iniciais onde quem criou é -1
std::vector<std::pair<std::string,int>> diskInstantiator(int size, std::vector<std::vector<std::string>> parsedFiles){
    std::vector<std::pair<std::string,int>> f(size);
    for(int i = 0; i<(int)parsedFiles.size(); i++){
        int start = std::stoi(parsedFiles[i][1]);
        int size = std::stoi(parsedFiles[i][2]);
        for(int j = start;j<start+size; j++){
            f[j] = {parsedFiles[i][0],-1};
        }
    }
    return f;
}
// retorna o arquivo de files.txt em uma tupla de {size, occupied, operações, inicialização}
std::tuple<int, std::vector<std::vector<std::string>>, std::vector<std::vector<std::string>>> parseFiles(std::string filesPath){
    int size;
    int occupied;
    int aux;
    std::vector<std::vector<std::string>> parsed;
    std::vector<std::vector<std::string>> parsedInit;
    std::ifstream file;
    std::string line;
    file.open(filesPath);
    int counter=0;
    while(std::getline(file, line)){
        switch(counter){
            case 0:
                size = stoi(line);
                break;
            case 1:
                occupied = stoi(line);
                break;
            default:
                std::vector<std::string> s = split(line,", ");
                if(occupied-- > 0){
                    parsedInit.push_back(s);                            
                } else {
                    parsed.push_back(s);
                }
                break;
        }
        counter++;
    }
    return {size, parsed, parsedInit};
}
// retorna o parse do arquivo de processos;
std::vector<std::vector<std::string>> parseProcesses(std::string processesPath){
    std::vector<std::vector<std::string>> v;
    std::ifstream file;
    std::string line;
    file.open(processesPath);
    while(std::getline(file, line)){
        std::vector<std::string> s = split(line,", ");
        v.push_back(s);
    }
    return v;
}

// void process_manager(std::vector<std::queue<Process>>* ready_processes, std::vector<bool>* u_mem, std::vector<bool>* s_mem){
//     //loop temporario
//     while(true){
//         // fila de tempo real possui processo
//         std::vector<Process>& fila = (*ready_processes)[0];
//         if((*ready_processes)[0].size()){
            
//             Process aux = (*ready_processes)[0].front();
            
//             if(aux.getRemainingTime()-1){
//                 aux.updateRunTime(1);
//             }else{
//                 aux.resetRunTime();
//             }


//         }
//     }
// }

int main(int argc, char *argv[]){
    
    std::string file_name;
    // ultimo path é o de files
    file_name = argv[argc-1];

    std::tuple<int, std::vector<std::vector<std::string>>, std::vector<std::vector<std::string>>> parsedFiles = parseFiles(file_name);

    std::vector<std::pair<std::string,int>> disk = diskInstantiator(std::get<0>(parsedFiles), std::get<2>(parsedFiles));

    // penultimo path é de processes
    file_name = argv[argc-2];

    std::vector<std::vector<std::string>> parsedProcesses = parseProcesses(file_name);

    std::vector<Process> processes = processInstantiator(parsedProcesses);

    return 0;
}