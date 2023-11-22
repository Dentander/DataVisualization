#pragma once
#include <string>
#include <vector>
#include <iostream>


class AppObject {
private:
	std::string _tag;
	int _updatePriority;
	int _drawPriority;
	bool _destroyOnLoad = true;
	bool _justInstantiated = true;

	static std::vector<AppObject*> _objects;

protected:
	virtual void OnInstaniate() {}
	virtual void OnStart() {}
	virtual void OnUpdate() {}
	virtual void OnDisabledUpdate() {}
	virtual void OnDraw() {}
	virtual ~AppObject() {}

public:
	bool enabled = true;

	AppObject* Instaniate(
		std::string tag = "None",
		int updatePriority = 0,
		int drawPriority = 0,
		bool destroyOnLoad = true
	);

	std::string GetTag();
	int GetUpdatePriority();
	int GetDrawPriority();

	static void UpdateScene();
	static void DrawScene();
	static void DestroyScene();
	static void DestroyAll();

	template <typename T>
	static T* GetObjectOfType() {
		for (auto* object : _objects) {
			if (object->enabled == false) { continue; }
			if (dynamic_cast<T*>(object)) { return dynamic_cast<T*>(object); }
		}
		return nullptr;
	}

	template <typename T>
	static std::vector<T*> GetObjectsOfType() {
		std::vector<T*> result;
		for (auto* object : _objects) {
			if (object->enabled == false) { continue; }
			if (dynamic_cast<T*>(object)) { result.push_back(dynamic_cast<T*>(object)); }
		}
		return result;
	}
};
