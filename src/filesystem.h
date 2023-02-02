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
        int findFile(std::string fileName);
        int findOwnerOfFile(std::string fileName);

    private:
        std::vector<std::pair<std::string,int>> disk;
        std::map<std::string, std::pair<int, int>> fileTable;
        std::vector<std::tuple<int, int, int, int, bool>> log;
};