#pragma once
#include <AdditionalStd/String.h>


struct DataFrameCell {
public:
	float vFloat = 0;
	std::string vString = "";

	DataFrameCell(std::string info);
	bool IsNan();
	bool IsNum();
};

