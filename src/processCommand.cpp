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
    std::cout << "Exiting GhostQL. Goodbye!\n";
    exit(0);
}

// Parses and tokenizes input string and routes to command processor
void process(SessionContext& ctx, const std::string& input) {
    std::string sql = qlp.toUpperCase(input);
    std::vector<std::string> tokens = qlp.tokenizer(sql);
    processCommand(ctx, tokens);
}

// Function to process parsed commands
void processCommand(SessionContext& ctx, std::vector<std::string>& tokens) {
    if (tokens.empty()) {
        std::cerr << "Empty command.\n";
        return;
    }

    std::string commandType = tokens[0];

    if (commandType == "EXIT") {
        exitProgram();
        return;
    }

    if (commandType == "USE") {
        if (tokens.size() < 2) {
            std::cerr << "Invalid USE command. Usage: USE <database>\n";
            return;
        }
        db.useDatabase(ctx, tokens);
        return;
    }

    if (commandType == "CREATE") {
        if (tokens.size() < 3) {
            std::cerr << "Invalid CREATE command. Usage: CREATE DATABASE|TABLE <name>\n";
            return;
        }

        std::string commandFunction = tokens[1];

        if (commandFunction == "DATABASE") {
            db.createDatabase(ctx, tokens);
            return;
        } else if (commandFunction == "TABLE") {
            db.createTable(ctx, tokens);
            return;
        } else{
            std::cerr << "Invalid command.\n";
            return;
        }
    }

    std::cerr << "Unsupported or unknown command.\n";
}
