#ifndef PARSER_H
#define PARSER_H

#include <string>

enum CommandType { INIT, ADD, COMMIT, LOG, CHECKOUT, CONFIG, BRANCH, MERGE, RESET, TAG, UNKNOWN };

CommandType parseCommand(const std::string& input);

#endif