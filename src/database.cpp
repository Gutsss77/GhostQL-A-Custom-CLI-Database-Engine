#include "database.hpp"
#include "session.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;
std::string storageName = "databases"; //name of folder which stores the databases of user

//creates a folder for users database
void Database::createDatabase(SessionContext& ctx, std::vector<std::string>& tokens) {
    std::cout << "Working!" << std::endl;
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

//creates folder in users database
void Database::createTable(SessionContext& ctx, std::vector<std::string>& tokens){
    if(ctx.activeDatabase == ""){
        std::cout << "No database is selected for use.\n";
        return;
    }
}