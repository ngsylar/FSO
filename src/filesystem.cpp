#include "filesystem.h"
#include<iostream>

FileSystem::FileSystem(std::vector<std::pair<std::string,int>> disk, std::vector<std::tuple<int, int, int, int, bool>> log)
{
    this->disk = disk;
    this->log = log; // log-> int1=pid, int2=operacao, int3=momento do erro na operacao, int4=primeiro bloco, bool= falha (false) ou sucesso (true)
    
    std::map<std::string, std::pair<int, int>> ft; // string=nome do arquivo, int1=primeira posicao, int2=tamanho do bloco
    std::string name;
    int start, size, count=0;
    for(int i=0; i< this->disk.size(); i++){
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

int FileSystem::findOwnerOfFile(std::string fileName){
    return this->disk[this->fileTable[fileName].first].second;
}

std::vector<std::pair<std::string,int>> FileSystem::doOperation(std::vector<std::string> operation, int priority)
{
    int pid = std::stoi(operation[0]);
    int opCode = std::stoi(operation[1]);
    std::string fileName = operation[2];
    int frst;
    bool flag = false;

    // verificar se o processo existe, senao coloca no log e retorna o disco

    switch(opCode){
            case 0: // 0 para criar um arquivo
            {
                int numBlocks = std::stoi(operation[3]);
                int counter = -1;
                for(int i=0; i<this->disk.size(); i++){
                    if(this->disk[i].first == "0"){
                        if(counter == -1){
                            frst = i;
                        }
                        counter++;
                    } else{
                        counter = -1;
                    }
                    if(counter == numBlocks-1){
                        for(int j=frst; j<frst+numBlocks; j++){
                            this->disk[j] = {fileName, pid};
                        }
                        this->fileTable[fileName] = {frst, numBlocks};
                        // coloca no log a mensagem de sucesso
                        this->log.push_back({pid, 0, -1, frst, true});
                        flag = true;
                        break;
                    }
                }
                if(flag == true) break;
                // não conseguiu alocar coloca no log a mensagem de falha
                this->log.push_back({pid, 0, -1, -1, false});
                break;

            }

            case 1: // 1 para deletar um arquivo
            {   // checar se o arquivo existe mesmo!!!
                if(fileTable.find(fileName) != fileTable.end()){
                    if(findOwnerOfFile(fileName) == pid || priority == 0){
                        for(int i = fileTable[fileName].first; i < fileTable[fileName].first+fileTable[fileName].second; i++){
                            this->disk[i] = {"0", -1};
                        }
                        this->fileTable.erase(fileName);
                        // coloca no log a msg de sucesso
                        this->log.push_back({pid, 1, -1, -1, true});

                    } else{
                        // se o processo não puder fazer a operação coloca no log
                        this->log.push_back({pid, 1, 1, -1, false});
                    }
                } else { // o arquivo não existe, entao coloca no log
                    this->log.push_back({pid, 1, 2, -1, false});
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
    for(int i=0; i< this->disk.size(); i++){
        std::cout << this->disk[i].first << ' ';
    }
    std::cout << std::endl;
}

std::vector<std::pair<std::string,int>> FileSystem::getDisk(){
   return this->disk;
}

std::vector<std::tuple<int, int, int, int, bool>> FileSystem::getLog(){
   return this->log;
}

std::map<std::string, std::pair<int, int>> FileSystem::getFileTable(){
   return this->fileTable;
}