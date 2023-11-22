#pragma once
#include <string>
#include <vector>


std::vector<std::string> Split(std::string line, std::string separator=" ");
std::string Replace(std::string line, char from, char to);
std::string ToString(char symbole);
int ToInt(std::string line);
float ToFloat(std::string line);