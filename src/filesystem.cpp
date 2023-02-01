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

int FileSystem::findFile(std::string fileName){
    return this->disk[this->fileTable[fileName].first];
}

int FileSystem::findOwnerOfFile(std::string fileName){
    return this->disk[this->fileTable[fileName].second];
}

std::vector<std::pair<std::string,int>> FileSystem::doOperation(std::vector<std::string> operation)
{
    int pid = std::stoi(operation[0]);
    int opCode = std::stoi(operation[1]);
    std::string fileName = operation[2];
    string msg;

    // verificar se o processo existe, senao coloca no log e retorna o disco

    switch(opCode){
            case 0: // 0 para criar um arquivo
                int numBlocks = std::stoi(operation[3]);
                int counter = 0;
                for(int i=0; i<this->disk.size(); i++){
                    if(counter == numBlocks){
                        msg = "O processo " + std::to_string(pid) + " criou o arquivo " + std::to_string(fileName) + " (blocos ";
                        for(int j=i-counter; j<numBlocks; j++){
                            disk[j] = {fileName, pid};

                            if(j == numBlocks-1){
                                msg += std::to_string(j) + ").";
                            } else{
                                msg += std::to_string(j) + ", ";
                            }
                        }
                        // coloca no log a mensagem de sucesso
                        this->log.push_back({true, msg});
                        break;
                    }
                    if(this->disk[i].first == 0){
                        counter++;
                    }
                }
                // não conseguiu alocar coloca no log a mensagem de falha
                msg = "O processo " + std::to_string(pid) + " não pode criar o arquivo " + std::to_string(fileName) + " (falta de espaço).";
                this->log.push_back({false, msg});
                break;

            case 1: // 1 para deletar um arquivo
                // checar se o arquivo existe mesmo!!!

                if(instantiatedProcesses[findFile(fileName).second].priority == 0 || findOwnerOfFile(fileName) == pid){
                    for(int i = fileTable[fileName].first; i < fileTable[fileName].second; i++){
                        disk[i] = {0, -1};
                    }
                    fileTable.erase(fileName);
                    // coloca no log
                    msg = "O processo " + std::to_string(pid) + " deletou o arquivo " + std::to_string(fileName) + ".";
                    this->log.push_back({true, msg});
                } else{
                    // se o processo não puder fazer a operaçãocoloca no log
                    
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

// colocar os arquivos que ja estavam no disco na tabela!!!