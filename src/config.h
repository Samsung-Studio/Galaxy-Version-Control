#ifndef CONFIG_H
#define CONFIG_H

#include <string>

extern std::string THEME;

void loadConfig();
void saveConfig();
void setTheme(std::string theme);

#endif