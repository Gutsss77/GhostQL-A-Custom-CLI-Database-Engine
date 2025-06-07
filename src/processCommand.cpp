#include "processCommand.hpp"
#include "database.hpp"
#include "QLParser.hpp"
#include <iostream>
#include <vector>
#include <string>

Database db;
QLParser qlp;

//for exiting the program;
void exitProgram() {
    std::cout << "Exiting GhostQL. Goodbye!\n";
    exit(0);
}

//function to process input commands
void processCommand(std::vector<std::string>& tokens){
    if (tokens.empty()) {
        std::cerr << "Empty command.\n";
        return;
    }
    std::string commandType = tokens[0];
    if(commandType == "EXIT"){
        exitProgram();
    }
    std::string commandFunction = tokens[1];

    if(commandType == "CREATE"){
        if(commandFunction == "DATABASE"){
            db.createDatabase(tokens);
            return;
        }else if(commandFunction == "TABLE"){
            
        }
    }
    std::cerr << "Unsupported or unknown command.\n";
}
