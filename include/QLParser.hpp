#ifndef QLPARSER_H
#define QLPARSER_H

#include "json.hpp"
#include <string>
#include <vector>

using json = nlohmann::ordered_json;

class QLParser {
private:
    //covert the string into vector of tokens
    std::vector<std::string> tokensOfCommand(const std::string& command);

public:
    //convert the string to uppercase
    std::string toUpperCase(const std::string& command);

    //return vector containing all uppercase tokens
    std::vector<std::string> tokenizer(const std::string& s);

    //creates meta data folder in users table for defining schemas
    json extractMetadataForTable(std::vector<std::string>& tokens);
};

#endif // QLPARSER_H
