#include "QLParser.hpp"
#include "database.hpp"
#include "columnMeta.hpp"
#include "json.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <cctype>

using json = nlohmann::ordered_json;

//convert the string to uppercase
std::string QLParser::toUpperCase(const std::string& command) {
    std::string upperCommand = command;
    std::transform(upperCommand.begin(), upperCommand.end(), upperCommand.begin(), ::toupper);
    return upperCommand;
}

//covert the string into vector of tokens (create advnace parser for handling the create table command)
// std::vector<std::string> QLParser::tokensOfCommand(const std::string& command) {
//     std::istringstream stream(command);
//     std::vector<std::string> tokens;
//     std::string token;
//     while (stream >> token) {
//         tokens.push_back(token);
//     }
//     return tokens;
// }
std::vector<std::string> QLParser::tokensOfCommand(const std::string& command) {
    std::vector<std::string> tokens;
    std::string token;

    //for handling the ( and ,
    for (char ch : command) {
        if (isspace(ch)) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else if (ch == ',' || ch == '(' || ch == ')') {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(std::string(1, ch));
        } else {
            token += ch;
        }
    }

    if (!token.empty()) {
        tokens.push_back(token);
    }

    return tokens;
}

//return vector containing all uppercase tokens
std::vector<std::string> QLParser::tokenizer(const std::string& s) {
    // std::string upper = toUpperCase(s);
    return tokensOfCommand(s);
}

//creates meta data folder in users table for defining schemas
json QLParser::extractMetadataForTable(std::vector<std::string>& tokens){
    std::string tableName = tokens[2];
    int n = tokens.size();
    int start = -1;
    int end = -1;

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
    if(start == -1 || end == -1){
        std::cerr << " ERROR : No Metadata is defined for table.\n";
        return schema;
    } 
    schema["tableName"] = tableName;
    schema["metaData"] = json::array();

    for(int i = start + 1; i < end; i += 3){
        schema["metaData"].push_back({ {"column_name", tokens[i]}, {"type", tokens[i + 1]} });
    }
    return schema;
}

std::vector<ColumnMeta> QLParser::extracTableMetaForInsert(std::vector<std::string>& tokens){
    std::vector<ColumnMeta> metadata;
    std::string tableName = tokens[2];
    ColumnMeta d1;
    d1.name = tableName;
    d1.type = "tableName"; //first entry is table name
    metadata.push_back(d1);

    return metadata;
}