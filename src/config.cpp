#include "config.h"
#include <iostream>
#include <fstream>

using namespace std;

string THEME = "dark";  // Default theme

void loadConfig() {
    ifstream configFile(".galaxy/config");
    if (configFile) {
        getline(configFile, THEME);
    }
    configFile.close();
}

void saveConfig() {
    ofstream configFile(".galaxy/config");
    configFile << THEME << endl;
    configFile.close();
}

void setTheme(string theme) {
    THEME = theme;
    saveConfig();
    cout << "🎨 Theme changed to " << theme << "!\n";
}