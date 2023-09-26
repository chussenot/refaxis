#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <hiredis/hiredis.h>
#include <nlohmann/json.hpp>
#include <uuid/uuid.h>  // For generating UUIDs

using json = nlohmann::json;

// Define your Redis server connection details
const char* REDIS_HOST = "localhost";
const int REDIS_PORT = 6379;

int main() {
    return 0;
}
