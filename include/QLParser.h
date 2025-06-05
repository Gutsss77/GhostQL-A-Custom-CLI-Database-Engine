#ifndef QLPARSER_H
#define QLPARSER_H

#include <string>
#include <vector>

class QLParser {
private:
    std::vector<std::string> tokensOfCommand(const std::string& command);

public:
    std::string toUpperCase(const std::string& command);
    std::vector<std::string> tokenizer(const std::string& s);
};

#endif // QLPARSER_H
