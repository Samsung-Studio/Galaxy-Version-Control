#include <iostream>
#include "parser.h"
#include "vcs.h"
#include "branch.h"
#include "config.h"

using namespace std;

int main() {
    loadConfig();  

    string input;
    cout << "\n🌌  Welcome to Galaxy VCS 🌌\n";
    cout << "------------------------------\n";

    while (true) {
        cout << "Galaxy > ";
        getline(cin, input);
        if (input == "exit") break;

        CommandType command = parseCommand(input);

        switch (command) {
            case INIT:
                initRepo();
                break;
            case ADD:
                cout << "Enter file name: ";
                getline(cin, input);
                addFile(input);
                break;
            case COMMIT:
                cout << "Enter commit message: ";
                getline(cin, input);
                commit(input);
                break;
            case LOG:
                showLog();
                break;
            case RESET:
                resetRepo();
                break;
            case TAG:
                cout << "Enter tag name: ";
                getline(cin, input);
                createTag(input);
                break;
            case BRANCH:
                cout << "Enter branch name: ";
                getline(cin, input);
                createBranch(input);
                break;
            case MERGE:
                cout << "Enter branch to merge: ";
                getline(cin, input);
                mergeBranch(input);
                break;
            case CONFIG:
                cout << "Enter theme (dark/light): ";
                getline(cin, input);
                setTheme(input);
                break;
            default:
                cout << "⚠️ Unknown command\n";
        }
    }

    cout << "👋 Exiting Galaxy VCS...\n";
    return 0;
}