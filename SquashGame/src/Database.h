#pragma once
#include "screencasts.h"

void addUser(std::string nome);
void visualUserList();
void addScoreboard(std::string nome, int score);
void visualScoreBoard();
void clearScoreboard();
void clearUserList();
bool defaultSettings();
bool readSettings();
bool updateSettings(bool sound);