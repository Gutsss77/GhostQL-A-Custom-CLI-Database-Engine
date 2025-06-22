#ifndef HELPER_H
#define HELPER_H

#include <json.hpp>
#include <string>
#include <filesystem>
#include <vector>

using json = nlohmann::ordered_json;
namespace fs = std::filesystem;

//function helper
class Helper {
public:
    std::vector<std::string> jsonColumnTokens(json schema, fs::path table);
    std::vector<std::string> columnNamesFromQuery(std::vector<std::string>& tokens);
    std::vector<std::vector<std::string>> valuesFromQuery(std::vector<std::string>& tokens);
};

#endif // HELPER_H
