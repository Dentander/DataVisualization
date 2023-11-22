#pragma once
#include <map>
#include <string>
#include <vector>
#include <AdditionalStd/String.h>


class DataFrame {
public:
	std::map<std::string, int> columns;
	std::vector<std::vector<int>> data;

	void ReadCsv(std::string name);
};

