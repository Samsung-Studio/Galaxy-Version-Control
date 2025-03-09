#include "vcs.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <ctime>

using namespace std;
namespace fs = filesystem;

void initRepo() {
    if (fs::exists(".galaxy")) {
        cout << "❌ Repository already initialized.\n";
        return;
    }
    fs::create_directory(".galaxy");
    fs::create_directory(".galaxy/objects");
    ofstream head(".galaxy/HEAD");
    head << "ref: refs/heads/main\n";
    head.close();
    cout << "✅ Initialized Galaxy repository.\n";
}

void addFile(string filename) {
    if (!fs::exists(filename)) {
        cout << "❌ Error: File not found!\n";
        return;
    }
    ofstream index(".galaxy/index", ios::app);
    string hash = hashFile(filename);
    index << filename << " " << hash << endl;
    
    fs::copy_file(filename, ".galaxy/objects/" + hash, fs::copy_options::overwrite_existing);
    cout << "✅ Added " << filename << " to staging area.\n";
}

void commit(string message) {
    ifstream index(".galaxy/index");
    if (!index) {
        cout << "No files to commit!\n";
        return;
    }

    string timestamp = to_string(time(nullptr));
    string commitData = "Commit: " + timestamp + "\nMessage: " + message + "\n";

    string line;
    while (getline(index, line)) {
        commitData += line + "\n";
    }
    index.close();
    
    string commitHash = hashString(commitData);
    ofstream commitFile(".galaxy/objects/" + commitHash);
    commitFile << commitData;
    commitFile.close();

    ofstream head(".galaxy/HEAD");
    head << commitHash;
    head.close();

    cout << "✅ Committed: " << commitHash.substr(0, 7) << " - " << message << endl;
}

void showLog() {
    ifstream head(".galaxy/HEAD");
    string commitHash;
    if (!head) {
        cout << "No commits found.\n";
        return;
    }
    getline(head, commitHash);
    head.close();

    while (!commitHash.empty()) {
        string commitFile = ".galaxy/objects/" + commitHash;
        if (!fs::exists(commitFile)) break;

        ifstream commitData(commitFile);
        cout << commitData.rdbuf() << endl;
        cout << "-----------------------\n";
        commitData.close();
        commitHash = "";
    }
}

void resetRepo() {
    fs::remove_all(".galaxy");
    cout << "🛑 Repository has been reset!\n";
}

void createTag(string tagName) {
    ofstream tagFile(".galaxy/tags/" + tagName);
    if (!tagFile) {
        cout << "❌ Could not create tag!\n";
        return;
    }
    ifstream head(".galaxy/HEAD");
    string commitHash;
    getline(head, commitHash);
    head.close();
    tagFile << commitHash;
    tagFile.close();
    cout << "🏷️  Tag created: " << tagName << endl;
}