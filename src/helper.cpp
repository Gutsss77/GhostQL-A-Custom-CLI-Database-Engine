#include "helper.hpp"
#include "QLParser.hpp"
#include <json.hpp>
#include <filesystem>
#include <iostream>

using json = nlohmann::ordered_json;
namespace fs = std::filesystem;
QLParser q;

std::vector<std::string> Helper::jsonColumnTokens(json schema, fs::path table) {
    std::vector<std::string> newTokens;
    for (const auto& i : schema["metaData"]) {
        if (i.contains("column_name")) {
            newTokens.push_back(i["column_name"]);
        }
    }
    return newTokens;
}

std::vector<std::string> Helper::columnNamesFromQuery(std::vector<std::string>& tokens) {
    int idxF = -1;
    int idxL = -1;
    int n = tokens.size();
    for (int i = 0; i < n; i++) {
        if (tokens[i] == "(") {
            idxF = i;
        }
        if (tokens[i] == ")") {
            idxL = i;
            break;
        }
    }

    std::vector<std::string> newTokens;
    for (int i = idxF + 1; i < idxL; i++) {
        if (tokens[i] != ",") {
            newTokens.push_back(tokens[i]);
        }
    }
    return newTokens;
}

std::vector<std::vector<std::string>> Helper::valuesFromQuery(std::vector<std::string>& tokens){
    std::vector<std::vector<std::string>> valuesSet;
    int n = tokens.size();
    int i = 0;
    while(i < n && q.toUpperCase(tokens[i]) != "VALUES"){
        i++;
    }

    if(i == n){
        std::cerr << " ERROR : 'VALUES' keyword not found.\n";
        return valuesSet;
    }

    i++; //moves to next token after VALUES
    while(i < n){
        if(tokens[i] == "("){
            std::vector<std::string> rowData;
            i++; // move after the '('
            while(i < n && tokens[i] != ")"){
                if(tokens[i] != ","){
                    std::string val = tokens[i];
                        //removes quotes from strings like ('Ghost') to (Ghost)
                    if(!val.empty() && val.front() == '\'' && val.back() == '\''){
                        val = val.substr(1, val.size() - 2);
                    }
                    rowData.push_back(val);
                }
                i++;
            }
            if(i == n || tokens[i] != ")"){
                std::cerr << " ERROR: Missing closing ')' in VALUES clause.\n";
                return valuesSet;
            }
            valuesSet.push_back(rowData);
        }
        i++;
    }
    return valuesSet;
}

std::vector<std::vector<std::string>> Helper::schemaOfTable(json &schema){
    std::vector<std::vector<std::string>> result;
    if(schema.contains("metaData") && schema["metaData"].is_array()){
        for(const auto& column : schema["metaData"]){
            if(column.contains("column_name") && column.contains("type")){
                std::string columnName = column["column_name"];
                std::string columnType = column["type"];
                result.push_back({columnName, columnType});
            }
        }
    }
    return result;
}