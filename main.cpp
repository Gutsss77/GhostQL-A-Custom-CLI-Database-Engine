#include <iostream>
#include <string>

int main(){
    std::string input;
    
    std::cout << "Welcome to the GQL monitor. Commands doesn't end with ';'.\n"
              << "Version: 1.0.0 GQL Server.\n"
              << "Type 'help' for help.\n" << std::endl;

    while(true){
        std::cout << "GhostQL>> ";
        std::getline(std::cin, input);

        
    }
    return 0;
}