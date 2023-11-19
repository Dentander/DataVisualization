#include <fstream>
#include <Systems/UserPrefs.h>
#include <AdditionalStd/String.h>


const std::string UserPrefs::_fileName = "data/Saves/UserPrefs.txt";
const char UserPrefs::_spaceReplacer = '`';

void UserPrefs::OnInstaniate() {
	ReadFromFile(_fileName);
}

UserPrefs::~UserPrefs() {
	SaveToFile(_fileName);
}

void UserPrefs::ReadFromFile(std::string fileName) {
	std::ifstream myfile(fileName);
	std::string line;
	while (getline(myfile, line)) {
		auto info = Split(line, " ");
		std::string valueType = info[0], valueName = info[1], value = info[2];
		if (valueType == "int") { _valuesInt[valueName] = ToInt(value); }
		if (valueType == "float") { _valuesFloat[valueName] = ToFloat(value); }
		if (valueType == "string") { _valuesString[valueName] = Replace(value, _spaceReplacer, ' '); }
	}
}

void UserPrefs::SaveToFile(std::string fileName) {
	std::ofstream file;
	file.open(fileName);
	for (auto& i : _valuesInt) { file << "int " << i.first << " " << i.second << "\n"; }
	for (auto& i : _valuesFloat) { file << "float " << i.first << " " << i.second << "\n"; }
	for (auto& i : _valuesString) { file << "string " << i.first << " " << Replace(i.second, ' ', _spaceReplacer) << "\n"; }
	file.close();
}

int UserPrefs::GetInt(std::string key, int defualtValue) {
	if (_valuesInt.find(key) == _valuesInt.end()) {
		_valuesInt[key] = defualtValue;
		return defualtValue;
	}
	return _valuesInt[key];
}

float UserPrefs::GetFloat(std::string key, float defualtValue) {
	if (_valuesFloat.find(key) == _valuesFloat.end()) {
		_valuesFloat[key] = defualtValue;
		return defualtValue;
	}
	return _valuesFloat[key];
}

std::string UserPrefs::GetString(std::string key, std::string defualtValue) {
	if (_valuesString.find(key) == _valuesString.end()) {
		_valuesString[key] = defualtValue;
		return defualtValue;
	}
	return _valuesString[key];
}

void UserPrefs::SetInt(std::string key, int value) { _valuesInt[key] = value; }
void UserPrefs::SetFloat(std::string key, float value) { _valuesFloat[key] = value; }
void UserPrefs::SetString(std::string key, std::string value) { _valuesString[key] = value; }

void UserPrefs::Clear() {
	_valuesInt.clear();
	_valuesFloat.clear();
	_valuesString.clear();
}
