#ifndef REMOTE_H
#define REMOTE_H

#include <string>

void pushChanges(const std::string& remoteURL);
void pullChanges(const std::string& remoteURL);
void cloneRepo(const std::string& remoteURL);

#endif