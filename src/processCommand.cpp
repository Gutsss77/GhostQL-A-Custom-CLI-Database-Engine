#include "processCommand.hpp"
#include "database.hpp"
#include "QLParser.hpp"
#include "session.hpp"
#include <iostream>
#include <vector>
#include <string>

// Global objects
Database db;
QLParser qlp;

// For exiting the program
void exitProgram() {
    std::cout << " Exiting GhostQL. Goodbye!\n";
    exit(0);
}

// Parses and tokenizes input string and routes to command processor
void process(SessionContext& ctx, const std::string& input) {
    // std::string sql = qlp.toUpperCase(input);
    std::vector<std::string> tokens = qlp.tokenizer(input);
    processCommand(ctx, tokens);
}

// Function to process parsed commands
void processCommand(SessionContext& ctx, std::vector<std::string>& tokens) {
    if (tokens.empty()) {
        std::cerr << " ERROR : Empty command.\n";
        return;
    }

    // std::string commandType = tokens[0];
    std::string commandType = qlp.toUpperCase(tokens[0]);

    if (commandType == "EXIT") {
        exitProgram();
        return;
    }

    if (commandType == "USE") {
        if (tokens.size() < 2) {
            std::cerr << " ERROR : Invalid USE command. Usage: USE <database>\n";
            return;
        }
        db.useDatabase(ctx, tokens);
        return;
    }

    if (commandType == "CREATE") {
        if (tokens.size() < 3) {
            std::cerr << " ERROR : Invalid CREATE command. Usage: CREATE DATABASE|TABLE <name>\n";
            return;
        }

        // std::string commandFunction = tokens[1];
        std::string commandFunction = qlp.toUpperCase(tokens[1]);

        if (commandFunction == "DATABASE") {
            db.createDatabase(ctx, tokens);
            return;
        } else if (commandFunction == "TABLE") {
            db.createTable(ctx, tokens);
            return;
        } else{
            std::cerr << " ERROR : Invalid command.\n";
            return;
        }
    }

    if(commandType == "SHOW"){
        if(tokens.size() < 2){
            std::cerr << " ERROR : Invalid SHOW command. Usage: SHOW DATABASES | SHOW TABLES\n";
            return;
        }
        // std::string commandFunction = tokens[1];
        std::string commandFunction = qlp.toUpperCase(tokens[1]);
        if(commandFunction == "DATABASES"){
            db.showDatabases(ctx, tokens);
            return;
        }else if(commandFunction == "TABLES"){
            db.showTables(ctx, tokens);
            return;
        }else{
            std::cerr << " ERROR : Invalid command.\n";
            return;
        }
    }

    if(commandType == "DROP"){
        if(tokens.size() > 3){
            std::cerr << " ERROR : Invalid DROP command. Usage : DROP <databasename> | DROP TABLE <tablename>\n";
            return;
        }
        std::string commandFunction = qlp.toUpperCase(tokens[1]);
        if(commandFunction == "DATABASE"){
            db.dropDatabase(ctx, tokens);
            return;
        }else if(commandFunction == "TABLE"){
            return;
        }else{
            std::cerr << " ERROR : Invalid command.\n";
            return;
        }
    }

    std::cerr << " ERROR : Unsupported or unknown command.\n";
}
