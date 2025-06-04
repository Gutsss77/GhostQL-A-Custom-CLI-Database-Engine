#include "processCommand.h"
#include "database.h"
#include "QLParser.h"
#include <iostream>
#include <vector>
#include <string>

Database db;
QLParser qlp;

void processCommand(std::vector<std::string>& tokens){
    if(tokens.size() < 3){
        std::cerr << "Invalid Command!";
        return;
    }
    std::string commandType = tokens[0];

    if(commandType == "CREATE"){
        db.createDatabase(tokens);
        return;
    }
}
