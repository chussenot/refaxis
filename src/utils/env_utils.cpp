#include "env_utils.h"
#include <iostream>
#include <cstring>

std::vector<std::pair<std::string, std::string>> getAllEnvironmentVariables() {
    std::vector<std::pair<std::string, std::string>> envVariables;
    extern char** environ;

    for (char** env = environ; *env != nullptr; ++env) {
        char* envVar = *env;
        char* separator = std::strchr(envVar, '=');
        if (separator != nullptr) {
            std::string name(envVar, separator - envVar);
            std::string value(separator + 1);
            envVariables.push_back(std::make_pair(name, value));
        }
    }

    return envVariables;
}

std::string getEnvironmentVariable(const std::string& name) {
    char* value = std::getenv(name.c_str());
    if (value != nullptr) {
        return std::string(value);
    }
    return "";
}
