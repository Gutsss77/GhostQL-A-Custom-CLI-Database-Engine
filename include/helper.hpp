#ifndef HELPER_H
#define HELPER_H

#include <json.hpp>
#include <string>
#include <filesystem>
#include <vector>

using json = nlohmann::ordered_json;
namespace fs = std::filesystem;

//helper for checking condition and statements
class Helper{
public:
    std::vector<std::string> jsonColumnTokens(json schema, fs::path table);
};

#endif //HELPER_H