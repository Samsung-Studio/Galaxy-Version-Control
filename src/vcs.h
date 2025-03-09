#ifndef VCS_H
#define VCS_H

#include <string>

void initRepo();
void addFile(std::string filename);
void commit(std::string message);
void showLog();
void checkout(std::string commitHash);
void resetRepo();
void createTag(std::string tagName);

#endif