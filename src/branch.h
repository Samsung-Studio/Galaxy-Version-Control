#ifndef BRANCH_H
#define BRANCH_H

#include <string>

void createBranch(const std::string& branchName);
void switchBranch(const std::string& branchName);
void listBranches();
void mergeBranch(const std::string& branchName);

#endif