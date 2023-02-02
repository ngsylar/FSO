#include "GlobalDefinitions.h"

MemoryManager::MemoryManager () {
    blocksCount = 1024;
    realTimeBlocksCount = 64;
    memory = std::vector<int>(blocksCount);
    segmentsBegin = new Segment(false, 0, 1024);
    lastPid = -1;
}

MemoryManager::Segment::Segment (bool filled, int address, int size, Segment* nextSegment) {
    this->filled = filled;
    this->address = address;
    this->size = size;
    this->nextSegment = nextSegment;
}

MemoryManager::~MemoryManager () {
    Segment* currentSegment,* nextSegment;
    currentSegment = segmentsBegin;
    do {
        nextSegment = currentSegment->nextSegment;
        delete(currentSegment);
    } while (nextSegment != nullptr);
}

int MemoryManager::Allocate (int priority, int blocksCount) {
    Segment* currentSegment = segmentsBegin;

    // editar: prioridade 0 vai pra area reservada

    // busca por um segmento livre para alocacao
    while (currentSegment != nullptr) {
        if ((not currentSegment->filled) and (currentSegment->size >= blocksCount)) {
            lastPid++;

            // se ha espaco suficiente para alocar memoria, preenche o espaco requisitado pelo processo
            int nextSegmentAddress = currentSegment->address + blocksCount;
            for (int i = currentSegment->address; i < nextSegmentAddress; i++)
                memory[i] = lastPid;
            currentSegment->filled = true;
            
            // se espaco disponivel no segmento eh maior que o requisitado, cria-se um novo segmento, livre
            if (currentSegment->size > blocksCount) {
                int newSegmentSize = currentSegment->size - blocksCount;
                currentSegment->size = blocksCount;

                Segment* newSegment = new Segment(
                    false, nextSegmentAddress, newSegmentSize, currentSegment->nextSegment
                );
                currentSegment->nextSegment = newSegment;
            }
            // retorna o pid do processo para alocacao bem sucedida
            return lastPid;
        }
        // se segmento esta ocupado ou se nao ha espaco suficiente, continua a busca
        currentSegment = currentSegment->nextSegment;
    }
    // se busca acabou e o segmento aponta para nulo, a alocacao nao pode ser realizada
    return -1;
}

bool MemoryManager::Deallocate (int pid, int address) {
    // editar: onde fica guardado os enderecos de cada processo?
    // na memoria, no proprio processo, no gerenciador de processos?

    if (memory[address] == pid) {
        Segment* currentSegment = segmentsBegin;
        while (currentSegment != nullptr) {

            if (currentSegment->address == address) {
                currentSegment->filled = false;

                Segment* nextSegment = currentSegment->nextSegment;
                if (not nextSegment->filled) {
                    currentSegment->nextSegment = nextSegment->nextSegment;
                    delete(nextSegment);
                }
                return true;
            }
            currentSegment = currentSegment->nextSegment;
        }
    } return false;
}

int MemoryManager::GetSize () {
    return blocksCount;
}

int MemoryManager::GetRealTimeSize () {
    return realTimeBlocksCount;
}

int MemoryManager::GetUserSize () {
    return (blocksCount - realTimeBlocksCount);
}