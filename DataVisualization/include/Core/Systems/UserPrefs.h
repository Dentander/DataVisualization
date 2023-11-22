#pragma once
#include <unordered_map>
#include <BaseClasses/AppObject.h>


class UserPrefs : public AppObject {
private:
	static const std::string _fileName;

	std::unordered_map<std::string, int> _valuesInt;
	std::unordered_map<std::string, float> _valuesFloat;
	std::unordered_map<std::string, std::string> _valuesString;

	void OnInstaniate();
	~UserPrefs();

	void ReadFromFile(std::string fileName);
	void SaveToFile(std::string fileName);

public:
	using AppObject::AppObject;

	int GetInt(std::string key, int defualtValue = 0);
	float GetFloat(std::string key, float defualtValue = 0.0f);
	std::string GetString(std::string key, std::string defualtValue = "None");

	void SetInt(std::string key, int value);
	void SetFloat(std::string key, float value);
	void SetString(std::string key, std::string value);

	void Clear();
};

