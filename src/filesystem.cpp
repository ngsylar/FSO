#include "filesystem.h"

FileSystem::FileSystem(std::vector<std::pair<std::string,int>> disk, std::map<string, pair<int, int>> fileTable, std::vector<pair<std::bool, std::string>> log)
{
    this->disk = disk;
    this->fileTable = fileTable;
    this->log = log;
}
FileSystem::FileSystem()
{
}

std::vector<std::pair<std::string,int>> FileSystem::doOperation(std::vector<std::string> operation)
{
    int pid = std::stoi(operation[0]);
    int opCode = std::stoi(operation[1]);
    std::string fileName = operation[2];

    switch(opCode){
            case 0:
                int numBlocks = std::stoi(operation[3]);
                int counter = 0;
                for(int i=0; i<this->disk.size(); i++){
                    if(counter == numBlocks){
                        for(int j=i-counter; j<numBlocks; j++){
                            disk[j] = {fileName, pid};
                        }
                        // colocar no log sucesso
                        break;
                    }
                    if(this->disk[i].first == 0){
                        counter++;
                    }
                }
                // não conseguiu alocar
                // log de erro
                break;

            case 1:
                // checar se o arquivo existe mesmo!!!

                if(instantiatedProcesses[disk[fileTable[fileName].first].second].priority == 0 || disk[fileTable[fileName]].second == pid){
                    for(int i = fileTable[fileName].first; i < fileTable[fileName].second; i++){
                        disk[i] = {0, -1};
                    }
                    fileTable.erase(fileName);
                    // coloca no log
                } else{
                    // se o processo não puder fazer a operação
                    // coloca no log
                }
                
                break;

            default:
                // Código de operação não existe
                break;
    }


    return this->disk;
}

void FileSystem::readLog()
{
    for(int i=1; i<=this->log.size(); i++){
        if(this->log[i].first == true){
            cout << "Operação " << i << " => Sucesso" << endl;
            cout << log[i].second << endl;
        } else{
            cout << "Operação " << i << " => Falha" << endl;
            cout << log[i].second << endl;
        }
    }
}