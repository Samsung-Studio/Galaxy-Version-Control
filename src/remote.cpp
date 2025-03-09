#include "remote.h"
#include <iostream>

using namespace std;

void pushChanges(const string& remoteURL) {
    cout << "🚀 Pushing changes to remote: " << remoteURL << endl;
}

void pullChanges(const string& remoteURL) {
    cout << "⬇️  Pulling changes from remote: " << remoteURL << endl;
}

void cloneRepo(const string& remoteURL) {
    cout << "📥 Cloning repository from: " << remoteURL << endl;
}