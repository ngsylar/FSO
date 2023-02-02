#include "filesystem.h"
#include<iostream>

FileSystem::FileSystem(std::vector<std::pair<std::string,int>> disk, std::vector<std::tuple<int, int, int, int, bool>> log)
{
    this->disk = disk;
    this->log = log; // log-> int1=pid, int2=operacao, int3=momento do erro na operacao, int4=primeiro bloco, bool= falha (false) ou sucesso (true)
    
    std::map<std::string, std::pair<int, int>> ft;
    std::string name;
    int start, size, count=0;
    for(int i=0; i<= this->disk.size(); i++){
        if(this->disk[i].first != "0" && count == 0){
            name = disk[i].first;
            start = i;
            count++;
        } else if((this->disk[i].first == "0" || this->disk[i].first != name) && count != 0){
            size = count;
            count = 0;
            ft[name] = {start, size};

            if(this->disk[i].first != "0"){
                name = disk[i].first;
                start = i;
                count++; 
            }
        } else if(this->disk[i].first == name && count != 0){
            count++;
        }
    }
    this->fileTable = ft;
}
FileSystem::FileSystem()
{
}

int FileSystem::findFile(std::string fileName){
    return this->disk[this->fileTable[fileName].first].second;
}

int FileSystem::findOwnerOfFile(std::string fileName){
    return this->disk[this->fileTable[fileName].second].second;
}

std::vector<std::pair<std::string,int>> FileSystem::doOperation(std::vector<std::string> operation, int priority)
{
    int pid = std::stoi(operation[0]);
    int opCode = std::stoi(operation[1]);
    std::string fileName = operation[2];
    int frst;

    // verificar se o processo existe, senao coloca no log e retorna o disco

    switch(opCode){
            case 0: // 0 para criar um arquivo
            {
                int numBlocks = std::stoi(operation[3]);
                int counter = 0;
                for(int i=0; i<this->disk.size(); i++){
                    if(counter == numBlocks){
                        for(int j=frst; j<numBlocks; j++){
                            disk[j] = {fileName, pid};

                        }
                        // coloca no log a mensagem de sucesso
                        this->log.push_back({pid, 0, -1, frst, true});
                        break;
                    }
                    if(this->disk[i].first == "0"){
                        if(counter == 0){
                            frst = i;
                        }
                        counter++;
                    } else{
                        counter = 0;
                    }
                }
                // não conseguiu alocar coloca no log a mensagem de falha
                this->log.push_back({pid, 0, -1, -1, false});
                break;

            }

            case 1: // 1 para deletar um arquivo
            {   // checar se o arquivo existe mesmo!!!

            
                if(findOwnerOfFile(fileName) == pid || priority == 0){
                    for(int i = fileTable[fileName].first; i < fileTable[fileName].second; i++){
                        disk[i] = {"0", -1};
                    }
                    fileTable.erase(fileName);
                    // coloca no log
                    this->log.push_back({pid, 1, -1, -1, true});

                } else{
                    // se o processo não puder fazer a operação coloca no log
                    this->log.push_back({pid, 1, -1, -1, false});
                }
                
                break;
            }

            default:
                // Código de operação não existe
                this->log.push_back({pid, opCode, -1, -1, false});
                break;
    }

    return this->disk;
}

void FileSystem::showDisk()
{
    std::cout << "Mapa de Ocupação do Disco: " << std::endl;
    for(int i=0; i<= this->disk.size(); i++){
        std::cout << this->disk[i].first << ' ';
    }
}
