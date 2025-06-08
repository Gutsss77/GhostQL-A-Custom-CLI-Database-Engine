#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <filesystem>

//Manages the active database to create session for user, helpful for :
/*
    1. Testing
    2. Mutiple users
*/
class SessionContext{
public:
    std::string activeDatabase;
    std::filesystem::path rootPath;

    SessionContext(const std::filesystem::path& root) : activeDatabase(""), rootPath(root) {}
};

#endif //SESSION_H