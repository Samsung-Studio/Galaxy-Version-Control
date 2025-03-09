#include "parser.h"
#include <sstream>
#include <vector>

CommandType parseCommand(const std::string& input) {
    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token) {
        tokens.push_back(token);
    }

    if (tokens.empty()) return UNKNOWN;

    std::string cmd = tokens[0];

    if (cmd == "new") return INIT;
    if (cmd == "stage") return ADD;
    if (cmd == "save") return COMMIT;
    if (cmd == "history") return LOG;
    if (cmd == "restore") return CHECKOUT;
    if (cmd == "config") return CONFIG;
    if (cmd == "branch") return BRANCH;
    if (cmd == "merge") return MERGE;
    if (cmd == "reset") return RESET;
    if (cmd == "tag") return TAG;

    return UNKNOWN;
}