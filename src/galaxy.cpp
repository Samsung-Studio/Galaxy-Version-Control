#include <iostream>
#include <string>
#include "parser.h"
#include "vcs.h"   // ✅ Includes only the header, avoiding duplicate function definitions
#include "utils.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: galaxy <command> [args]\n";
        return 1;
    }

    string cmd = argv[1];
    CommandType command = parseCommand(cmd);

    switch (command) {
        case INIT:
            initRepo();
            break;
        case ADD:
            if (argc < 3) cout << "Usage: galaxy add <file>\n";
            else addFile(argv[2]);
            break;
        case COMMIT:
            if (argc < 3) cout << "Usage: galaxy commit \"message\"\n";
            else commit(argv[2]);
            break;
        case LOG:
            showLog();
            break;
        case CHECKOUT:
            if (argc < 3) cout << "Usage: galaxy checkout <commit_hash>\n";
            else checkout(argv[2]);
            break;
        default:
            cout << "Unknown command\n";
    }
    return 0;
}