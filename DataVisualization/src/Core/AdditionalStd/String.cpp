#include <AdditionalStd/String.h>


std::vector<std::string> Split(std::string line, std::string separator) {
    std::vector<std::string> res;
    int end = line.find(separator);
    while (end != -1) {
        res.push_back(line.substr(0, end));
        line.erase(line.begin(), line.begin() + end + 1);
        end = line.find(separator);
    }
    if (line.substr(0, end).empty() == false) { res.push_back(line.substr(0, end)); }
    return res;
}

std::string Replace(std::string line, char from, char to) {
    for (auto& s : line) {
        if (s == from) { s = to; }
    }
    return line;
}

int ToInt(std::string line) {
    return atoll(line.c_str());
}

float ToFloat(std::string line) {
    return atof(line.c_str());
}
