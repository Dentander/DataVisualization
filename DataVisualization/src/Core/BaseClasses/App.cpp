#include <stdlib.h>
#include <BaseClasses/App.h>
#include <Systems/Input.h>
#include <Systems/Screen.h>
#include <Systems/SystemsLoader.h>


void App::Start() {
	SystemsLoader* _systemsLoader = new SystemsLoader();
	_systemsLoader->Instaniate();
}

void App::Run() {
	while (true) {
		Update();
		Draw();
	}
	Exit();
}

void App::Update() { 
	AppObject::UpdateScene(); 
}

void App::Draw() { 
	AppObject::DrawScene(); 
}

void App::Exit() {
	AppObject::DestroyScene();
	AppObject::DestroyAll();
	exit(0);
}
