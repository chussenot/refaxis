#ifndef ENV_UTILS_H
#define ENV_UTILS_H

#include <string>
#include <vector>

// Function to get all environment variables and their values
std::vector<std::pair<std::string, std::string>> getAllEnvironmentVariables();

// Function to get the value of a specific environment variable
std::string getEnvironmentVariable(const std::string& name);

#endif // ENV_UTILS_H
