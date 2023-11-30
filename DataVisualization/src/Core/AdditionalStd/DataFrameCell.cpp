#include <AdditionalStd/DataFrameCell.h>


DataFrameCell::DataFrameCell(std::string info) {
	if (IsFloat(info))              { vFloat  = ToFloat(info); }
	else if (info.empty() == false) { vString = info;          } 
	else                            { vString = "Nan";         }
}

bool DataFrameCell::IsNan() {
	return vString == "Nan";
}

bool DataFrameCell::IsNum() {
	return vString.empty();
}
