#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "MediaLibrary.h"

class CommandLineInterface {
private:
    MediaLibrary library;

    void displayHelp();
    std::vector<std::string> splitCommand(const std::string& command);
    void processCommand(const std::vector<std::string>& args);

public:
    void run();
};