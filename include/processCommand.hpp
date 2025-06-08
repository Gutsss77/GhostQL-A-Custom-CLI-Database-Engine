#ifndef PROCESS_COMMAND_H
#define PROCESS_COMMAND_H

#include "session.hpp"
#include <string>
#include <vector>

void process(SessionContext& ctx, const std::string& input);
void processCommand(SessionContext& ctx, std::vector<std::string>& tokens);
void exitProgram();

#endif // PROCESS_COMMAND_H
