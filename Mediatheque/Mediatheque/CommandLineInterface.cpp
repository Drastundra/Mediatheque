#include "CommandLineInterface.h"

#include <sstream>
#include <algorithm>

void CommandLineInterface::displayHelp() {
    std::cout << "Available commands:\n"
        << "addClient name firstname age address phoneNumber mail\n"
        << "removeClient identifier\n"
        << "listClient\n"
        << "addMedia type [details]\n"
        << "removeMedia type title\n"
        << "listMedia [status]\n"
        << "help\n"
        << "exit\n";
}

std::vector<std::string> CommandLineInterface::splitCommand(const std::string& command) {
    std::vector<std::string> tokens;
    std::istringstream iss(command);
    std::string token;

    while (iss >> std::quoted(token)) {
        tokens.push_back(token);
    }

    return tokens;
}

void CommandLineInterface::processCommand(const std::vector<std::string>& args) {
    if (args.empty()) return;

    const std::string& cmd = args[0];

    if (cmd == "help") {
        displayHelp();
    }
    // Implémentez les autres commandes ici
}

void CommandLineInterface::run() {
    std::string input;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "exit") break;

        auto args = splitCommand(input);
        processCommand(args);
    }
}