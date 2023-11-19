#include <BaseClasses/Scene.h>


void Scene::Load() {
	AppObject::DestroyScene();
	Instaniate();
}

