#include "session.hpp"
#include "processCommand.hpp"
#include <iostream>
#include <string>

//session context with the root directory
SessionContext ctx(SOURCE_DIR);

int main() {
    std::string input;

    std::cout << "Welcome to the GhostQL DBMS.\n"
              << "Version: 1.0.0 GhostQL Server.\n"
              << "Type 'EXIT' to quit.\n" << std::endl;

    while (true) {
        std::cout << "[GhostQL>  ";
        std::getline(std::cin, input);
        if (!input.empty()) {
            process(ctx, input);
        }
    }

    return 0;
}
