#include <Visualization/Data.h>


void Data::OnStart() {}

std::vector<DataFrameCell>& Data::GetColumnX() {
	return (*this)[columnX];
}

std::vector<DataFrameCell>& Data::GetColumnY() {
	return (*this)[columnY];
}

std::vector<DataFrameCell>& Data::GetColumnZ() {
	return (*this)[columnZ];
}
