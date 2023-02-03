#include<vector>
#include<map>
#include<string>
#include<fstream>
#include<iostream>

class FileSystem {
    public:
        FileSystem();
        FileSystem(
            std::vector<std::pair<std::string,int>> disk,
            std::vector<std::tuple<int, int, int, int, bool>> log);
        std::vector<std::pair<std::string,int>> doOperation(std::vector<std::string> operation, int priority);
        void showDisk();
        int findOwnerOfFile(std::string fileName);
        std::vector<std::pair<std::string,int>> getDisk();
        std::vector<std::tuple<int, int, int, int, bool>> getLog();
        std::map<std::string, std::pair<int, int>> getFileTable();

    private:
        std::vector<std::pair<std::string,int>> disk;
        std::map<std::string, std::pair<int, int>> fileTable;
        std::vector<std::tuple<int, int, int, int, bool>> log;
};