#include <algorithm>
#include <BaseClasses/AppObject.h>


AppObject* AppObject::Instaniate(Tag tag, int updatePriority, int drawPriority, bool destroyOnLoad) {
	_tag = tag;
	_updatePriority = updatePriority;
	_drawPriority = drawPriority;
	_destroyOnLoad = destroyOnLoad;
	_objects.push_back(this);
	return this;
}

Tag AppObject::GetTag() {
	return _tag; 
}

int AppObject::GetUpdatePriority() { 
	return _updatePriority; 
} 

int AppObject::GetDrawPriority() { return _drawPriority; }


// ========== STATIC ==========

std::vector<AppObject*> AppObject::_objects;

void AppObject::UpdateScene() {
	// ========== SORT BY PRIORITY ==========
	std::sort(_objects.begin(), _objects.end(), [](AppObject* a, AppObject* b) {
		return a->GetUpdatePriority() < b->GetUpdatePriority();
	});

	for (size_t i = 0; i < _objects.size(); ++i) {
		auto* object = _objects[i];
		if (object->_justInstantiated == true) { object->OnInstaniate(); }
	}

	for (size_t i = 0; i < _objects.size(); ++i) {
		auto* object = _objects[i];
		if (object->enabled == false) { continue; }
		if (object->_justInstantiated == true) { object->OnStart(); }
	}

	for (auto* object : _objects) { object->_justInstantiated = false; }

	for (size_t i = 0; i < _objects.size(); ++i) {
		auto* object = _objects[i];
		if (object->enabled == true) { object->OnUpdate(); }
		else { object->OnDisabledUpdate(); }
	}
} 

void AppObject::DrawScene() {
	// ========== SORT BY PRIORITY ==========
	std::sort(_objects.begin(), _objects.end(), [](AppObject* a, AppObject* b) {
		return a->GetDrawPriority() < b->GetDrawPriority();
	});

	for (auto* object : _objects) {
		if (object->enabled == false) { continue; }
		object->OnDraw();
	}
}

void AppObject::DestroyScene() {
	std::vector<AppObject*> notDestroyedObjects;
	for (auto* object : _objects) {
		if (object->_destroyOnLoad == false) { notDestroyedObjects.push_back(object); }
		else { delete object; }
	}
	_objects.clear();
	_objects = notDestroyedObjects;
}

void AppObject::DestroyAll() {
	for (auto* object : _objects) { delete object; }
	_objects.clear();
}
