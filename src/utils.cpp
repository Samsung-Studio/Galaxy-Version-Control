#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <openssl/sha.h>

using namespace std;

string hashFile(string filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "❌ Error: Could not open file " << filename << endl;
        return "";
    }

    stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return hashString(buffer.str());
}

string hashString(string data) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), hash);

    stringstream ss;
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        ss << hex << (int)hash[i];
    }
    return ss.str();
}