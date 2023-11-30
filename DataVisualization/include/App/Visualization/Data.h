#pragma once
#include <BaseClasses/AppObject.h>
#include <AdditionalStd/DataFrame.h>


class Data : public AppObject, public DataFrame {
private:
	void OnStart();

public:
	bool isReady = false;

	float radius = 1;
	std::string columnX = "None";
	std::string columnY = "None";
	std::string columnZ = "None";
	std::string columnTarget;

	std::vector<DataFrameCell>& GetColumnX();
	std::vector<DataFrameCell>& GetColumnY();
	std::vector<DataFrameCell>& GetColumnZ();
};
