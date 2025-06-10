#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include "session.hpp"
#include <vector>

class Database{
public:
    void createDatabase(SessionContext& ctx, std::vector<std::string>& tokens);
    void showDatabases(SessionContext& ctx, std::vector<std::string>& tokens);
    void useDatabase(SessionContext& ctx, std::vector<std::string>& tokens);
    void createTable(SessionContext& ctx, std::vector<std::string>& tokens);
};



#endif //DATABASE_H