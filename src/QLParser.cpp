#include "QLParser.h"
#include <algorithm>
#include <sstream>
#include <cctype>

std::string QLParser::toUpperCase(const std::string& command) {
    std::string upperCommand = command;
    std::transform(upperCommand.begin(), upperCommand.end(), upperCommand.begin(), ::toupper);
    return upperCommand;
}

std::vector<std::string> QLParser::tokensOfCommand(const std::string& command) {
    std::istringstream stream(command);
    std::vector<std::string> tokens;
    std::string token;
    while (stream >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<std::string> QLParser::tokenizer(const std::string& s) {
    std::string upper = toUpperCase(s);
    return tokensOfCommand(upper);
}

