#include "database.hpp"
#include "QLParser.hpp"
#include "session.hpp"
#include "columnMeta.hpp"
#include "helper.hpp"
#include "json.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <filesystem>
#include <sstream>
#include <fstream>

namespace fs = std::filesystem;
std::string storageName = "databases"; //name of folder which stores the databases of user
using json = nlohmann::ordered_json;
Helper hp;

//creates a folder for users database
void Database::createDatabase(SessionContext& ctx, std::vector<std::string>& tokens) {
    if(tokens.size() < 3){
        std::cerr << " ERROR : Invalid Command!" << "\n";
        return;
    }
    fs::path databasesDir = ctx.rootPath / storageName;
    fs::path dbName = databasesDir / tokens[2];

    try {
        if (!fs::exists(databasesDir)) {
            fs::create_directories(databasesDir);
        }

        if (fs::exists(dbName)) {
            std::cerr << " ERROR : Can't create database '" << dbName << "' database exists\n";
        } else {
            fs::create_directory(dbName);
            std::cout << " Query OK, Database '" << tokens[2] << "' created successfully.\n";
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << " Filesystem error: " << e.what() << "\n";
    }
}

//Shows all the databases created by user's
void Database::showDatabases(SessionContext& ctx, std::vector<std::string>& tokens){
    if(tokens.size() < 2){
        std::cerr << " ERROR : Invalid Command.\n";
        return;
    }
    fs::path db = ctx.rootPath / storageName;
    if(!fs::exists(db)){
        std::cerr << " ERROR : No database found.\n";
        return;
    }
    try{
        std::cout << " Databases : \n\n";
        int row = 0;
        for(const auto& dir : fs::directory_iterator(db)){
            if(dir.is_directory()){
                std::cout << " - " << dir.path().filename().string() << "\n";
                row++;
            }
        }
        if(row == 1){
            std::cout << row << " row in set." << "\n";
        }else{
            std::cout << row << " rows in set." << "\n";
        }
    }catch(const std::exception& e){
        std::cerr << " ERROR : while traversing the directory. " << e.what() << "\n";
    }
}

void Database::showTables(SessionContext& ctx, std::vector<std::string>& tokens){
    if(tokens.size() < 2){
        std::cerr << " ERROR : Invalid Command.\n";
    }
    if(ctx.activeDatabase.empty()){
        std::cout << " ERROR : No database is selected for performing operations.\n";
        return;
    }
    fs::path db = ctx.rootPath / storageName / ctx.activeDatabase / "metadata";
    if(!fs::exists(db)){
        std::cerr << " ERROR : No database found.\n";
        return;
    }
    try{
        std::cout << " Tables in " << ctx.activeDatabase << "\n\n";
        int row = 0;
        for(const auto& dir : fs::directory_iterator(db)){
            if(dir.is_regular_file() && dir.path().extension() == ".meta"){
                std::cout << " - " << dir.path().filename().string() << "\n";
                row++;
            }
        }
        if(row == 1){
            std::cout << row << " row in set." << "\n";
        }else{
            std::cout << row << " rows in set." << "\n";
        }
    }catch(const std::exception& e){
        std::cerr << " ERROR : while traversing the directory. " << e.what() << "\n";
    }

}

//deletes database 
void Database::dropDatabase(SessionContext& ctx, std::vector<std::string>& tokens){
    if (tokens.size() != 3) {
        std::cerr << " ERROR: Invalid DROP DATABASE command. Usage: DROP <database_name>\n";
        return;
    }

    std::string db = tokens[2];
    fs::path dbName = ctx.rootPath / storageName / db;
    try{
        if(fs::exists(dbName)){
            fs::remove_all(dbName);
            std::cout << " Database " << db << " dropped successfully.\n";

            //if the db was in use
            if(ctx.activeDatabase != ""){
                ctx.activeDatabase = "";
            }
        }else{
            std::cout << " Database " << db << " does not exist.\n"; 
        }
    }catch(const fs::filesystem_error& e){
        std::cerr << " Filesystem error: " << e.what() << "\n"; 
    }
}

//set an active database for perfroming tasks
void Database::useDatabase(SessionContext& ctx, std::vector<std::string>& tokens){
    if(tokens.size() != 2){
        std::cerr << " ERROR : Invalid Command.\n";
        return;
    }
    std::string db = tokens[1];
    fs::path dbName = ctx.rootPath/ storageName / db;

    try{
        if(fs::exists(dbName)){
            ctx.activeDatabase = db;
            std::cout << " Database changed.\n";
            return;
        }else{
            std::cerr << " ERROR : Database does not exist.\n";
            return;
        }
    }catch(const fs::filesystem_error& e){
        std::cerr << " Filesystem error: " << e.what() << "\n";
    }
}

//creates a folder for table schema inside active database the structure is already defined (check readme.md to Create tables)
void Database::createTable(SessionContext& ctx, std::vector<std::string>& tokens){
    if(ctx.activeDatabase.empty()){
        std::cout << " ERROR : No database is selected for performing operations.\n";
        return;
    }
    std::string db = ctx.activeDatabase;
    fs::path dbPath = ctx.rootPath / storageName / db;

    //new folder to hold the metadata(in metadata folder inside active database) for table and its data (in data folder inside active database)
    fs::path metadataPath = dbPath / "metadata";
    fs::path dataPath = dbPath / "data";

        if (!fs::exists(metadataPath)) {
        fs::create_directories(metadataPath);
    }

    if (!fs::exists(dataPath)) {
        fs::create_directories(dataPath);
    }


    QLParser qlp;
    json schema = qlp.extractMetadataForTable(tokens);

    std::string tableName = schema["tableName"];
    fs::path metaFile = metadataPath / (tableName + ".meta");
    fs::path dataFile = dataPath / (tableName + ".data");

    if(fs::exists(metaFile)){
        std::cout << " ERROR : Table '" << tableName << "' already exists.\n";
        return;
    }

    try {
    // Place the JSON into tableName.meta
    std::ofstream outMeta(metaFile);
    outMeta << schema.dump(4);
    outMeta.close();

    // Place an empty data array into tableName.data
    std::ofstream outData(dataFile);
    outData << "[]";
    outData.close();

    } catch (const std::exception& e) {
        std::cerr << " ERROR : writing table files: " << e.what() << std::endl;
    }

    std::cout << " Table '" << tableName << "' created successfully.\n";

}

//insert the data into .data file of the table
void Database::insertIntoTable(SessionContext& ctx, std::vector<std::string>& tokens){
    if(tokens.size() < 6){
        std::cerr << " ERROR : Invalid Command.\n";
        return;
    }
    if(ctx.activeDatabase.empty()){
        std::cout << " ERROR : No database is selected for performing operations.\n";
        return;
    }
    std::string tableName = tokens[2];
    fs::path tablePath = ctx.rootPath / storageName /ctx.activeDatabase / "metadata" / (tableName + ".meta");

    if(!fs::exists(tablePath)){
        std::cerr << " ERROR : No table exists.\n";
        return;
    }

    //compares the tokens of query and stored json to validate the column names
    std::vector<std::string> t1 = hp.columnNamesFromQuery(tokens);

    std::ifstream inFile(tablePath);
    std::ostringstream buffer;
    buffer << inFile.rdbuf();
    std::string input = buffer.str();

    try{
        json meta = json::parse(input);
        std::vector<std::string> t2 = hp.jsonColumnTokens(meta, tablePath);
        if (t1 != t2) {
            std::cerr << " ERROR : Column mismatch in insert statement.\n";
        return;
    }
    }catch(const std::exception& e){
        std::cerr << " ERROR : " << e.what() << "\n";
    }
    std::vector<std::vector<std::string>> valueSet = hp.valuesFromQuery(tokens);
    
}

void Database::dropTable(SessionContext& ctx, std::vector<std::string>& tokens){
    if(ctx.activeDatabase.empty()){
        std::cout << " ERROR : No database is selected for performing operations.\n";
        return;
    }
    if(tokens.size() != 3){
        std::cerr << " ERROR: Invalid DROP TABLE command. Usage: DROP TABLE <table_name>\n";
        return;
    }

    std::string db = ctx.activeDatabase;
    std::string tableName = tokens[2];
    fs::path dbName = ctx.rootPath / storageName / db;
    //for meta data
    fs::path tableMeta = ctx.rootPath / storageName / db / "metadata" / (tableName + ".meta");
    //for table data
    fs::path tableData = ctx.rootPath / storageName / db / "data" / (tableName + ".data");

    try{
        if(fs::exists(dbName)){
            bool removedMeta = false;
            bool removedData = false;

            if (fs::exists(tableMeta)){
                fs::remove(tableMeta);
                removedMeta = true;
            }

            if (fs::exists(tableData)){
                fs::remove(tableData);
                removedData = true;
            }

            if (removedMeta || removedData){
                std::cout << " Table " << tableName << " dropped successfully.\n";
            } else {
                std::cerr << " ERROR : Table " << tableName << " does not exist in database.\n";
            }

        }else{
            std::cerr << " ERROR : Database does not exist.\n";
            return;
        }
    }catch(const fs::filesystem_error& e){
        std::cerr << " Filesystem error: " << e.what() << "\n";
    }
}