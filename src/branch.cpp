#include "branch.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

void createBranch(const string& branchName) {
    if (fs::exists(".galaxy/branches/" + branchName)) {
        cout << "❌ Branch already exists!\n";
        return;
    }
    fs::create_directory(".galaxy/branches/" + branchName);
    ofstream branchFile(".galaxy/branches/" + branchName + "/HEAD");
    branchFile << "ref: " + branchName;
    branchFile.close();
    cout << "✅ Created new branch: " << branchName << endl;
}

void switchBranch(const string& branchName) {
    if (!fs::exists(".galaxy/branches/" + branchName)) {
        cout << "❌ Branch not found!\n";
        return;
    }
    ofstream head(".galaxy/HEAD");
    head << "ref: " + branchName;
    head.close();
    cout << "🔄 Switched to branch: " << branchName << endl;
}

void listBranches() {
    cout << "🌿 Available Branches:\n";
    for (const auto& entry : fs::directory_iterator(".galaxy/branches")) {
        cout << "  - " << entry.path().filename().string() << endl;
    }
}

void mergeBranch(const string& branchName) {
    if (!fs::exists(".galaxy/branches/" + branchName)) {
        cout << "❌ Branch not found!\n";
        return;
    }
    cout << "🔄 Merging branch " << branchName << " into current branch...\n";
}