#include "parser.h"

CommandType parseCommand(const std::string& cmd) {
    if (cmd == "init") return INIT;
    if (cmd == "add") return ADD;
    if (cmd == "commit") return COMMIT;
    if (cmd == "log") return LOG;
    if (cmd == "checkout") return CHECKOUT;
    return UNKNOWN;
}