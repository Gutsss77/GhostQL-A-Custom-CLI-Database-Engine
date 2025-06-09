#include "database.hpp"
#include "QLParser.hpp"
#include "session.hpp"
#include "json.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;
std::string storageName = "databases"; //name of folder which stores the databases of user
using json = nlohmann::ordered_json;

//creates a folder for users database
void Database::createDatabase(SessionContext& ctx, std::vector<std::string>& tokens) {
    if(tokens.size() < 3){
        std::cerr << "Invalid Command!" << "\n";
        return;
    }
    fs::path databasesDir = ctx.rootPath / storageName;
    fs::path dbName = databasesDir / tokens[2];

    try {
        if (!fs::exists(databasesDir)) {
            fs::create_directories(databasesDir);
        }

        if (fs::exists(dbName)) {
            std::cerr << "Database already exists: " << dbName << "\n";
        } else {
            fs::create_directory(dbName);
            std::cout << "Database '" << tokens[2] << "' created successfully.\n";
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << "\n";
    }
}

//set an active database for perfroming tasks
void Database::useDatabase(SessionContext& ctx, std::vector<std::string>& tokens){
    if(tokens.size() != 2){
        std::cerr << "Invalid Command.\n";
    }
    std::string db = tokens[1];
    fs::path dbName = ctx.rootPath/ storageName / db;

    try{
        if(fs::exists(dbName)){
            ctx.activeDatabase = db;
            std::cout << "Activated database " << db << ".\n";
            return;
        }else{
            std::cerr << "Database does not exist.\n";
            return;
        }
    }catch(const fs::filesystem_error& e){
        std::cerr << "Filesystem error: " << e.what() << "\n";
    }
}

//creates a folder for table schema inside active database the structure is already defined (check readme.md 2. Create tables)
void Database::createTable(SessionContext& ctx, std::vector<std::string>& tokens){
    if(ctx.activeDatabase == ""){
        std::cout << "No database is selected for use.\n";
        return;
    }
    std::string db = ctx.activeDatabase;
    fs::path dbPath = ctx.rootPath / storageName / db;

    //new folder to hold the metadata(in metadata folder inside active database) for table and its data (in data folder inside active database)
    fs::path metadataPath = dbPath / "metadata";
    fs::path dataPath = dbPath / "data";

    fs::create_directories(metadataPath);
    fs::create_directories(dataPath);

    QLParser qlp;
    json schema = qlp.extractMetadataForTable(tokens);

    std::string tableName = schema["tableName"];
    fs::path metaFile = tableName + ".meta";
    fs::path dataFile = dataPath / ".data";

    if(fs::exists(metaFile)){
        std::cout << "Table '" << tableName << "' already exists.\n";
        return;
    }

    try{

    }catch()

}