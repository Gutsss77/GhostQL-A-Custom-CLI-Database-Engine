#ifndef QLPARSER_H
#define QLPARSER_H

#include <string>
#include <vector>

class QLParser {
private:
    std::string toUpperCase(const std::string& command);
    std::vector<std::string> tokensOfCommand(const std::string& command);

public:
    std::vector<std::string> tokenizer(const std::string& s);
    std::string getUpper(const std::string& command);
};

#endif // QLPARSER_H
