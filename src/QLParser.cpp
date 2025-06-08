#include "QLParser.hpp"
#include "database.hpp"
#include "json.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <cctype>

using json = nlohmann::json;

//convert the command to uppaercase
std::string QLParser::toUpperCase(const std::string& command) {
    std::string upperCommand = command;
    std::transform(upperCommand.begin(), upperCommand.end(), upperCommand.begin(), ::toupper);
    return upperCommand;
}

//covert the string into vector of tokens
std::vector<std::string> QLParser::tokensOfCommand(const std::string& command) {
    std::istringstream stream(command);
    std::vector<std::string> tokens;
    std::string token;
    while (stream >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

//return vector containing all uppercase tokens
std::vector<std::string> QLParser::tokenizer(const std::string& s) {
    std::string upper = toUpperCase(s);
    return tokensOfCommand(upper);
}

//creates meta data folder in users table for defining schemas
void extractMetadataForTable(std::vector<std::string>& tokens, const std::string& dbName){
    if(tokens.size() < 5){
        std::cerr << "Invalid Command! too Short.\n";
        return;
    }
    std::string tableName = tokens[2]; //table name

    //for finding the first open and first closing bracket tok extract the meta data db tables
    int n = tokens.size();
    int start = 0;
    int end = 0;
    for(int i = 0; i < n; i++){
        if(tokens[i] == "("){
            start = i;
        }
        if(tokens[i] == ")"){
            end = i;
            break;
        }
    }

}