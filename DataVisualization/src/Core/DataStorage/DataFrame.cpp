#include <iostream>
#include <fstream>
#include <string>
#include <DataStorage/DataFrame.h>


void DataFrame::ReadCsv(std::string name) {
    std::fstream file;
    std::string line;
    file.open(name);
    if (file.is_open()) {
        getline(file, line);
        auto cols = Split(line);
        for (int i = 0; i < cols.size(); ++i) { columns[cols[i]] = i; }
        while (getline(file, line)) {
            std::vector<int> nums;
            for (auto& i : Split(line)) { nums.push_back(ToFloat(i)); }
            data.push_back(nums);
        }
        file.close();
    }
}