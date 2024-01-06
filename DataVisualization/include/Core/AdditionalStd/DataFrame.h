#pragma once
#include <vector>
#include <unordered_map>
#include <AdditionalStd/DataFrameCell.h>


class DataFrame {
private:
	std::unordered_map<std::string, std::vector<DataFrameCell>> _data;
	std::unordered_map<std::string, float> _dataMin;
	std::unordered_map<std::string, float> _dataMax;
	size_t _size = 0;

public:
	bool ReadCsv(const std::string& fileName);
	void Cache();

	size_t GetSize();
	float GetMin(std::string column);
	float GetMax(std::string column);
	std::vector<char*> GetColumns();

	std::vector<DataFrameCell>& operator[](const std::string& column);
};

