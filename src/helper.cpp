#include <helper.hpp>
#include <json.hpp>
#include <QLParser.hpp>
#include <filesystem>
#include <iostream>
#include <vector>
#include <string>

using json = nlohmann::ordered_json;
namespace fs = std::filesystem;


std::vector<std::string> Helper::jsonColumnTokens(json schema, fs::path table){
    std::vector<std::string> newTokens;
    json j = json::parse(schema);

    for(const auto& i : j["metaData"]){
        if(i.contains("column_name")){
            newTokens.push_back(i["column_name"]);
        }
    }
    return newTokens;
}
