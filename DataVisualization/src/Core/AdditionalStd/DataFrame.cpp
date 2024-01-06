#include <iostream>
#include <fstream>
#include <limits>
#include <AdditionalStd/DataFrame.h>


bool DataFrame::ReadCsv(const std::string& fileName) {
    // ========== CLEAR ==========
    _data.clear();

    std::fstream file;
    std::string line;

    file.open(fileName);
    if (file.is_open() == false) { return false; }

    // ========== COLUMNS ==========
    getline(file, line);
    auto cols = Split(line, ",");
    
    // ========== READ ALL DATA ==========
    while (getline(file, line)) {
        auto cells = Split(line, ",");
        for (size_t i = 0; i < cells.size(); ++i) {
            _data[cols[i]].push_back(DataFrameCell(cells[i]));
        }
    }
    file.close();

    _size = _data.begin()->second.size();
    Cache();
    return true;
}

void DataFrame::Cache() {
    for (auto& column : _data) {
        float maxValue = std::numeric_limits<float>::min();
        float minValue = std::numeric_limits<float>::max();
        for (auto& value : column.second) {
            if (value.IsNum()) {
                maxValue = std::max(maxValue, value.vFloat);
                minValue = std::min(minValue, value.vFloat);
            }
        }
        _dataMax[column.first] = maxValue;
        _dataMin[column.first] = minValue;
    }
}

size_t DataFrame::GetSize() {
    return _size;
}

float DataFrame::GetMin(std::string column) {
    return _dataMin[column];
}

float DataFrame::GetMax(std::string column) {
    return _dataMax[column];
}

std::vector<char*> DataFrame::GetColumns() {
    std::vector<char*> res;
    for (auto& i : _data) {  res.push_back(const_cast<char*>(i.first.c_str())); }
    return res;
}

std::vector<DataFrameCell>& DataFrame::operator[](const std::string& column) {
    return _data[column];
}
