#ifndef PARSER_H
#define PARSER_H

#include <string>

enum CommandType { INIT, ADD, COMMIT, LOG, CHECKOUT, UNKNOWN };

CommandType parseCommand(const std::string& cmd);

#endif