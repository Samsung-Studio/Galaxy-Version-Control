#include "vcs.h"
#include "utils.h"  // ✅ Ensures hashing functions are accessible
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <ctime>

using namespace std;
namespace fs = filesystem;

void initRepo() {
    if (fs::exists(".galaxy")) {
        cout << "Repository already exists.\n";
        return;
    }
    fs::create_directory(".galaxy");
    fs::create_directory(".galaxy/objects");
    ofstream head(".galaxy/HEAD");
    head << "ref: refs/heads/main\n";
    head.close();
    cout << "Initialized Galaxy repository.\n";
}

void addFile(string filename) {
    if (!fs::exists(filename)) {
        cout << "Error: File not found!\n";
        return;
    }
    ofstream index(".galaxy/index", ios::app);
    string hash = hashFile(filename);
    index << filename << " " << hash << endl;
    
    fs::copy_file(filename, ".galaxy/objects/" + hash, fs::copy_options::overwrite_existing);
    cout << "Added " << filename << " to staging area.\n";
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

    cout << "Committed: " << commitHash.substr(0, 7) << " - " << message << endl;
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

void checkout(string commitHash) {
    string commitFile = ".galaxy/objects/" + commitHash;

    if (!fs::exists(commitFile)) {
        cout << "Error: Commit not found!\n";
        return;
    }

    ifstream commitData(commitFile);
    string line;
    vector<pair<string, string>> files;

    while (getline(commitData, line)) {
        if (line.find("Commit:") == 0 || line.find("Message:") == 0) {
            continue;
        }
        string filename, hash;
        stringstream ss(line);
        ss >> filename >> hash;
        files.push_back({filename, hash});
    }
    commitData.close();

    for (auto &entry : files) {
        string filename = entry.first;
        string hash = entry.second;
        string objectFile = ".galaxy/objects/" + hash;

        if (!fs::exists(objectFile)) {
            cout << "Warning: File " << filename << " not found in objects\n";
            continue;
        }

        fs::copy_file(objectFile, filename, fs::copy_options::overwrite_existing);
        cout << "Restored: " << filename << endl;
    }

    ofstream head(".galaxy/HEAD");
    head << commitHash;
    head.close();

    cout << "Checked out to commit: " << commitHash << endl;
}