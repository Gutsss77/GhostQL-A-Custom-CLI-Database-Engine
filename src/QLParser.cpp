#include "QLParser.hpp"
#include "database.hpp"
#include "json.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <cctype>

using json = nlohmann::ordered_json;

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
json extractMetadataForTable(std::vector<std::string>& tokens){
    std::string tableName = tokens[2];
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

    json schema;
    schema["tableName"] = tableName;
    schema["metaData"] = json::array();

    for(int i = start + 1; i < end; i += 3){
        schema["metaData"].push_back({ 
            {"column_name", tokens[i]}, 
            {"type", tokens[i + 1]}
        });
    }

    return schema;

}
