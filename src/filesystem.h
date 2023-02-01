class FileSystem {
    public:
        FileSystem();
        FileSystem(
            std::vector<std::pair<std::string,int>> disk,
            std::map<string, pair<int, int>> fileTable, 
            std::vector<pair<std::bool, std::string>> log);
        std::vector<std::pair<std::string,int>> doOperation(std::vector<std::string> operation);
        void FileSystem::readLog();
        int FileSystem::findFile(std::string fileName);
        int FileSystem::findOwnerOfFile(std::string fileName);

    private:
        std::vector<std::pair<std::string,int>> disk;
        std::map<string, pair<int, int>> fileTable;
        std::vector<pair<std::bool, std::string>> log;
};